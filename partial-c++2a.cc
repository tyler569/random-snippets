
#include <iostream>

template <typename Function, typename... CurryArgs>
constexpr auto partial_n(Function f, CurryArgs... value) {
    return [f, value...] <typename... ExtraArgs> (ExtraArgs... args) {
        return f(value..., args...);
    };
}

template <typename Function, typename CurryArg>
constexpr auto partial(Function f, CurryArg value) {
    return [f, value] <typename... ExtraArgs> (ExtraArgs... args) {
        return f(value, args...);
    };
}


constexpr int add(int a, int b, int c) {
    return a + b + c;
}

template <typename... T>
constexpr int add_n(T... v) {
    return (v + ...);
}

auto add2 = partial(add, 2);
auto add_n2 = partial(add_n<int, int, int, int>, 2);
auto add_nn9 = partial_n(add_n<int, int, int, int>, 2, 3, 4);

const int foo = add2(100, 100);
const int bar = add_n2(100, 200, 300);
const int baz = add_nn9(400);

int main() {
    std::cout << add_n2(bar, foo, baz) << '\n';
}

