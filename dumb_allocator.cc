
#include <utility>
#include <vector>
using std::size_t;

template <typename T>
struct alloc {
    using value_type = T;
    T *allocate(size_t count) {
        return nullptr;
    }
    void deallocate(T *ptr, size_t count) {
        return;
    }
    void destroy(T *ptr) {
        ptr->~T();
    }
};

std::vector<int, alloc<int>> x = {};

int main() {
    x.push_back(1);
}
