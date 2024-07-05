#include <array>
#include <iostream>
#include <sstream>

class IPv4 {
  public:
    constexpr IPv4() : ipv4_{ {0} } {}
    IPv4(unsigned char a, unsigned char b,
         unsigned char c, unsigned char d) : ipv4_{{a, b, c, d}} {}
    explicit IPv4(unsigned long a) : ipv4_{{static_cast<unsigned char>((a >> 24) & 0xFF),
                                            static_cast<unsigned char>((a >> 16) & 0xFF),
                                            static_cast<unsigned char>((a >> 8) & 0xFF),
                                            static_cast<unsigned char>(a & 0xFF)}} {}
    IPv4(const IPv4& other) noexcept : ipv4_(other.ipv4_) {}
    IPv4& operator=(const IPv4& other) noexcept {
        if (this != &other) {
            ipv4_ = other.ipv4_;
        }
        return *this;
    }

    std::string ToString() const {
        std::stringstream sstr;
        sstr << *this;
        return sstr.str();
    }

    unsigned long ToULong() const noexcept {
        return (static_cast<unsigned long>(ipv4_[0] << 24) |
                static_cast<unsigned long>(ipv4_[1] << 16) |
                static_cast<unsigned long>(ipv4_[2] << 8) |
                static_cast<unsigned long>(ipv4_[3]));
    }

    friend std::ostream& operator<<(std::ostream& out, const IPv4& obj) {
        out << static_cast<int>(obj.ipv4_[0]) << '.'
            << static_cast<int>(obj.ipv4_[1]) << '.'
            << static_cast<int>(obj.ipv4_[2]) << '.'
            << static_cast<int>(obj.ipv4_[3]);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, IPv4& obj) {
        char d1{}, d2{}, d3{};
        int b1{}, b2{}, b3{}, b4{};
        in >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if (d1 == '.' && d2 == '.' && d3 == '.') {
            obj = IPv4(b1, b2, b3, b4);
        }
        else {
            in.setstate(std::ios_base::failbit);
        }
        return in;
    }

  private:
    std::array<unsigned char, 4> ipv4_;
};

int main() {
    IPv4 a(168, 192, 0, 1);
    std::cout << a << std::endl;
    std::cout << a.ToString() << std::endl;

    IPv4 b = a;
    IPv4 c;
    c = b;

    IPv4 ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if (!std::cin.fail()) {
        std::cout << ip << std::endl;
    }
}
