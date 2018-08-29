
enum class Error {
    OutOfMemory,
};

template <typename T, typename Err = Error>
struct err {
    bool is_error;
    union {
        T value;
        Err error;
    };
};
template <typename T, typename Err = Error>
err<T, Err> value(T&& v) {
    err<T, Err> ret = { false };
    ret.value = v;
    return ret;
}
template <typename T, typename Err = Error>
err<T, Err> error(Err&& e) {
    err<T, Err> ret = { false };
    ret.error = e;
    return ret;
}

#define try(...) { auto _v = (__VA_ARGS__); if(_v.is_error){return _v;} }

err<int> could_error(int x) {
    if (x < 0) {
        return error<int>(Error::OutOfMemory);
    } else {
        return value(x + 1);
    }
}

err<int> catch_error(int y) {
    try(could_error(-5));
    return value(0);
}

int main() {
    auto v = catch_error(-9);
    if (v.is_error) {
        return -1;
    } else {
        return 0;
    }
}
