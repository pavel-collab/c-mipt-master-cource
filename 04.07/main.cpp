#include <iostream>

template <unsigned long N>
struct Fibbonachi {
    static constexpr unsigned long value = Fibbonachi<N-1>::value + Fibbonachi<N-2>::value;
};

template <>
struct Fibbonachi<0> {
    static constexpr unsigned long value = 1;
};

template <>
struct Fibbonachi<1> {
    static constexpr unsigned long value = 1;
};

template <int N> constexpr unsigned long fibbonachi = Fibbonachi<N>::value; 

int main() {
    // 1 1 2 3 5 8 13
    unsigned long fib = fibbonachi<6>; // expected 13
    std::cout << fib << std::endl;
}