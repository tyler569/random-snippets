
#include <iostream>

template <typename... Args>
constexpr void print_to(std::ostream& os, Args const&... args) {
    ((os << args), ...);
}

template <typename... Args>
constexpr void print(Args const&... args) {
    print_to(std::cout, args...);
}

int main() {
    print("Hello", " ", "World!", '\n');
}

