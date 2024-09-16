#include <iostream>
#include <cmath>
#include <numbers>

/*

build: g++ exponenta.cpp --std=c++20

*/

// Релизация численного решения нелинейного уравнения N*ln(N) - N - K*ln(10) = 0
// методом Ньютона для определения количества слагаемых N в ряде 
// для достижения заданной точности K (количество знаков после десятичной точки)
long long Newtons_M(unsigned long K, double init_x) {
    unsigned steps = 0;
    double accuracy = 1e-6;
    double x_cur = init_x;
    double x_prev = 0;

    while(abs(x_cur - x_prev) > accuracy) {
        x_prev = x_cur;
        steps+=1;
        x_cur = x_prev - (x_prev*log(x_prev) - x_prev - K*log(10)) / (log(x_prev));
    }

    return static_cast<long long>(std::floor(x_cur));
}

int main() {
    int accuracy;
    std::cin >> accuracy;

    long long value_numbers = Newtons_M(accuracy, 3.0);
    double cur = 1.0;
    double res = 0.0;

    for (auto i = 0; i < value_numbers +1 ; i++) {
        res += cur;
        cur /= i+1;
    }

    printf("My result:      %0.20f\n", res);
    printf("library result: %0.20f\n", std::numbers::e);
}