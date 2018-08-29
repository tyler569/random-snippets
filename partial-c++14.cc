
#include <iostream>
#include <utility>

/* needs -fconcepts (auto parameter)
template <typename Function>
constexpr auto partial_g(Function f, auto... values) {
   return [f, values...] (auto... args) {
       return f(values..., args...);
   };
} */

/* needs -std=c++2a (template lambda)
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
} */

/* needs c++14 (auto return + auto lambda parameters) */
template <typename Function, typename... CurryArgs>
constexpr auto partial_n14(Function f, CurryArgs... value) noexcept {
    return [f, value...] (auto... args) {
        return f(value..., args...);
    };
}

constexpr int add(int a, int b, int c) {
    return a + b + c;
}

/* needs c++17 (fold expr) */
template <typename... T>
constexpr int add_n(T... v) {
    return (v + ...);
}

void add_g(const char *prelude, int a, double b, char post) {
    std::cout << prelude << (static_cast<double>(a) + b) << post;
}

auto add2 = partial_n14(add, 2);
auto add_n2 = partial_n14(add_n<int, int, int, int>, 2);
auto add_nn9 = partial_n14(add_n<int, int, int, int>, 2, 3, 4);

auto print_add_g_1 = partial_n14(add_g, "data > ", 1);

const int foo = add2(100, 100);
const int bar = add_n2(100, 200, 300);
const int baz = add_nn9(400);

int main() {
    std::cout << add_n2(foo, bar, baz) << '\n';
    print_add_g_1(4.9, '\n');
}

