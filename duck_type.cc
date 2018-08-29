
#include <cstdio>
#include <vector>
using std::vector;

template <typename T>
auto sum_collection(T collection) {
    typename T::value_type sum = 0;
    for (auto const& val : collection) {
        sum += val;
    }
    return sum;
}

int main() {
    vector<int> x = {1, 2, 3, 4, 5};
    vector<double> y = {2, 3, 4, 5, 6, 7.2};

    printf("%i\n", sum_collection(x));
    printf("%f\n", sum_collection(y));
}
