
#include <iostream>

struct hex {
    int v;

    hex(int v) : v(v) {}
};

struct flag_saver {
    std::ostream& os;
    std::ios_base::fmtflags flags;

    flag_saver(std::ostream& os)
      : os(os) {
        flags = os.flags();
    }
    ~flag_saver() {
        os.flags(flags);
    }
};

std::ostream& operator << (std::ostream& os, hex hex_value) {
    flag_saver f { os };
    os << std::hex << hex_value.v;
    return os;
}

int main() {
    std::cout << 4 << ", 0x" << hex(10) << "\n";
}

