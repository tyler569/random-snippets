
#include <exception>
#include <iostream>

int main() {
    try {
        try {
            throw 1;
        } catch (int e) {
            std::cout << std::uncaught_exceptions() << '\n';
            throw 2;
        }
    } catch (int e) {
        std::cout << std::uncaught_exceptions() << '\n';
    }
    std::cout << std::uncaught_exceptions() << '\n';
}

