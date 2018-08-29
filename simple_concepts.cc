
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
concept bool ToStringable = requires (T v) {
    { std::to_string(v) } -> std::string;
    ! std::is_convertible_v<T, std::string>;
};

auto operator+ (std::string lhs, ToStringable rhs) { // -> std::string {
    return lhs + std::to_string(rhs);
}

auto bar(auto baz) {
    return baz + 10;
}

auto main() -> int {
    auto x = bar(10);
    auto y = bar("foobar");

    std::cout << x << " " << y << "\n";
}

