
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct allocation {
    void *ptr;
    size_t len;
};

typedef struct allocation mem;

struct allocator {
    mem (*alloc)(struct allocator *, size_t);
    void (*dealloc)(struct allocator *, mem);
    bool (*owns)(struct allocator *, mem);
};

typedef struct allocator allocator;

struct mallocator {
    mem (*alloc)(struct mallocator *, size_t);
    void (*dealloc)(struct mallocator *, mem);
    bool (*owns)(struct mallocator *, mem);
    bool debug;
};

typedef struct mallocator mallocator;

mem mallocator_alloc(mallocator *allocr, size_t len) {
    void *m = malloc(len);
    if (allocr->debug) {
        assert(m);
    }
    mem out = { m, len };
    return out;
}

void mallocator_dealloc(mallocator *allocr, mem m) {
    free(m.ptr);
}

void init_mallocator(mallocator *m) {
    m->alloc = mallocator_alloc;
    m->dealloc = mallocator_dealloc;
    m->owns = NULL;
}


struct fallback_allocator {
    mem (*alloc)(struct fallback_allocator *, size_t);
    void (*dealloc)(struct fallback_allocator *, mem);
    bool (*owns)(struct fallback_allocator *, mem);
    allocator *first;
    allocator *second;
};

typedef struct fallback_allocator fallback_allocator;

mem fallback_allocator_alloc(fallback_allocator *allocr, size_t len) {
    mem m = allocr->first->alloc(allocr->first, len);
    if (m.ptr != NULL) {
        return m;
    }
    return allocr->second->alloc(allocr->second, len);
}

void fallback_allocator_dealloc(fallback_allocator *allocr, mem m) {
    if (allocr->first->owns(allocr->first, m)) {
        allocr->first->dealloc(allocr->first, m);
        return;
    }
    if (allocr->second->owns(allocr->second, m)) {
        allocr->second->dealloc(allocr->second, m);
        return;
    }
    assert(false); // Did not actually own that memory!
}

bool fallback_allocator_owns(fallback_allocator *allocr, mem m) {
    if (! allocr->first->owns) {
        assert(false); // cannot meaningfully define this
    }
    if (allocr->first->owns(allocr->first, m)) {
        return true;
    }
    if (! allocr->second->owns) {
        // what do?
        return false;
    }
    return allocr->second->owns(allocr->second, m);
}

void init_fallback_allocator(fallback_allocator *f, allocator *first, allocator *second) {
    f->alloc = fallback_allocator_alloc;
    f->dealloc = fallback_allocator_dealloc;
    f->owns = fallback_allocator_owns;
    f->first = first;
    f->second = second;
}


struct null_allocator {
    mem (*alloc)(struct null_allocator *, size_t);
    void (*dealloc)(struct null_allocator *, mem);
    bool (*owns)(struct null_allocator *, mem);
};

typedef struct null_allocator null_allocator;

mem null_allocator_alloc(null_allocator *allocr, size_t len) {
    mem m = { NULL, len };
}

void null_allocator_dealloc(null_allocator *allocr, mem m) {
    if (m.ptr != NULL) {
        assert(false); // Did not actually own that memory!
    }
}

bool null_allocator_owns(null_allocator *allocr, mem m) {
    return m.ptr == NULL;
}

void init_null_allocator(null_allocator *n) {
    n->alloc = null_allocator_alloc;
    n->dealloc = null_allocator_dealloc;
    n->owns = null_allocator_owns;
}


null_allocator nullocator;
mallocator default_allocator;
fallback_allocator fb_allocator;

#define m_alloc(allocator, len) allocator.alloc(&allocator, len)
#define m_dealloc(allocator, mem) allocator.dealloc(&allocator, mem)

int main() {
    init_null_allocator(&nullocator);
    init_mallocator(&default_allocator);
    init_fallback_allocator(&fb_allocator, (allocator *)&nullocator, (allocator *)&default_allocator);

    mem x = m_alloc(default_allocator, sizeof(100));
    m_dealloc(default_allocator, x);

    mem y = m_alloc(fb_allocator, sizeof(int[100]));
    for (int i = 0; i<y.len; i++) {
        ((int *)y.ptr)[i] = i + 10;
    }
    printf("%i\n", ((int *)y.ptr)[10]);
    m_dealloc(fb_allocator, y);
}

