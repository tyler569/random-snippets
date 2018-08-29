
#include <algorithm>
#include <iostream>
#include <string>

using std::string;

template <typename Iterator>
bool starts_with(Iterator str, Iterator prefix) {
    return std::equal(prefix.begin(), prefix.end(), str.begin());
}

int main() {
    string foo = "This is a thing";
    string bar = "This";
    string baz = "this";

    std::cout << starts_with(foo, bar) << '\n';
    std::cout << starts_with(foo, baz) << '\n';

    return 0;
}

