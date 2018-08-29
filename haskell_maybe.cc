
#include <cassert>
#include <functional>

template <typename T>
struct Maybe {
    bool has_value;
    T value;

    Maybe(bool h, T v)
        : has_value(h), value(v) {}

    Maybe(bool h) {
        assert(!h);
        has_value = false;
    }

    T value_or(T orelse) {
        if (has_value) {
            return value;
        } else {
            return orelse;
        }
    }
};

template <typename T>
Maybe<T> Just(T val) {
    return Maybe<T>{true, val};
}

template <typename T>
Maybe<T> None() {
    return Maybe<T>{false};
}

template <typename T>
Maybe<T> even(T val) {
    if (val & 1) {
        return None<T>();
    } else {
        return Just<T>(val);
    }
}

template<typename T, typename U>
Maybe<U> operator >>= (Maybe<T> v, Maybe<U>(*f)(T)) {
    if (v.has_value) {
        return f(v.value);
    } else {
        return None<U>();
    }
}

int main() {
    auto x = even(10);
    auto y = x >>= even<int>;

    return y.value_or(0);
}

