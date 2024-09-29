#include <iostream>
#include <vector>

/*

Правильная скобочная последовательность:
- может быть пустой
- содержит равное число открывающихся и закрывающихся скобор
- всегда начинается с открытой скобки (кроме случая пустой последовательности)
- всегда кончается закрытой скобкой (кроме случая пустой последовательности)

Пусть A, B -- правильные скобочные последовательности. Тогда
'(A)B' -- правильная скобочная последовательность. количество пар скобок в  этой
скобочной последовательности N, а количество пар скобок в правильной скобочной последовательности A -- i.
Тогда количество пар скобок в последовательности B -- (N - i - 1).

Пусть F(k) -- функция, которая вычисляет количество правильных скобочных последовательностей с количеством пар скобок  k.
Тогда для нашей скобочной последовательности '(A)B' F(N) = sum^{i = 0}_{N-1} F(i) * F(N - i - 1)
(так как для любой последовательности A мы можем перебрать все доступные виды последовательности B).

Краевой случай: F(0) = 1 (считаем пустую скобочную последовательность валидной), F(1) = 1 (очевидно).
*/

size_t get_braket_sequences_number(size_t N) {
    if (N == 0)
        return 1; // считаем пустую скобочную последовательность тоже валидной

    if (N == 1)
        return 1;

    int res = 0;
    for (size_t i = 0; i < N; i++) {
        res += get_braket_sequences_number(i) * get_braket_sequences_number(N - i - 1);
    }
    return res;
}

int main() {
    size_t N;
    std::cin >> N; // N is a number of PAIRS
    
    std::cout << get_braket_sequences_number(N) << std::endl;
    return 0;
}