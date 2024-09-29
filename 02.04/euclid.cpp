#include <iostream>
#include <numeric>

int recursive_gcd(int x, int y) {
    if (y == 0)
        return x;
    return recursive_gcd(y, x % y);
}

int non_recursive_gcd(int x, int y) {
    while (x != 0 && y != 0) {
        if (x > y)
            x = x % y;
        else
            y = y % x;
    }

    return x + y;
}

int lcm(int a, int b) {
    return a / recursive_gcd(a, b) * b;   //используя форму a * b / gcd(a, b),
                                //можно получить переполнение на этапе a * b,
                                //поэтому следует выполнять деление до умножения
}

int main() {
    int a, b;
    std::cout << "input a: ";
    std::cin >> a;

    std::cout << "input b: ";
    std::cin >> b;

    std::cout << recursive_gcd(a, b) << std::endl;
    std::cout << non_recursive_gcd(a, b) << std::endl;
}