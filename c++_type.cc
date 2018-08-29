
#include <iostream>

template <typename T>
const char *f(T) {
    return __PRETTY_FUNCTION__;
}

#define type_thing(val) std::cout << #val << " : " << f(val) << '\n';

int bar(int) { return *(int *)1; }

int main() {
    auto foo = [] {};

    type_thing(foo);
    type_thing(f<int>);
    type_thing(main);
    type_thing(bar);
}

