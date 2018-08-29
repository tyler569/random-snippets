
#include <cstdio>

template <typename T>
struct const_ref;

template <typename T>
struct mut_ref;

struct unsafe_op {};

template <typename T>
struct safe_ptr {
    long refcnt;
    T *data;

    safe_ptr() : refcnt(0), data(new T) {}
    safe_ptr(T val) : refcnt(0), data(new T)
    {
        *data = val;
    }
    ~safe_ptr() { delete data; }
    safe_ptr(safe_ptr const&) = delete;

    const_ref<T> take_const() {
        if (refcnt >= 0)
            return const_ref<T>{this};
        else
            throw unsafe_op{};
    }

    mut_ref<T> take_mut() {
        if (refcnt == 0)
            return mut_ref<T>{this};
        else
            throw unsafe_op{};
    }

    const_ref<T> operator &() {
        return take_const();
    }

    mut_ref<T> operator +() {
        return take_mut();
    }
};

template <typename T>
struct const_ref {
    safe_ptr<T>& ptr;

    const_ref(safe_ptr<T> *upstream)
        : ptr(*upstream)
    {
        ptr.refcnt += 1;
    }

    ~const_ref() {
        ptr.refcnt -= 1;
    }

    T const& operator *() {
        return *ptr.data;
    }
};

template <typename T>
struct mut_ref {
    safe_ptr<T>& ptr;

    mut_ref(safe_ptr<T> *upstream)
        : ptr(*upstream)
    {
        ptr.refcnt -= 1;
    }

    ~mut_ref() {
        ptr.refcnt += 1;
    }

    T& operator *() {
        return *ptr.data;
    }
};

struct mut_{};
mut_ mut;
template <typename T>
mut_ref<T> operator &(mut_, safe_ptr<T>& s) {
    return s.take_mut();
}

int main() {
    safe_ptr<int> x { 1 };

    {
        auto ref = &x;
        printf("%i\n", *ref);
    }

    {
        auto mut_ref = mut& x;
        *mut_ref = 10;
        printf("%i\n", *mut_ref);
    }

    {
        auto ref = &x;
        printf("%i\n", *ref);
    }
}

