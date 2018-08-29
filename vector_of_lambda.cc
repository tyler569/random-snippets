
#include <cstdio>
#include <functional>
#include <vector>

std::vector<std::function<void()>> lambdas;

int main() {
    for (int i=0; i<10; i++) {
        lambdas.push_back([i] { printf("%i\n", i); });
    }

    for (auto l : lambdas) {
        l();
    }
}

