#include <iostream>

/*
Основная задача функции -- переместить пирамидку со стартового штыря (№1)
на целевой штырь.

k -- целевой штырь
N -- количество дисков в пирамидке
i -- номер перемещаемого в данный момент диска


*/
void hanoi(int N, int i, int k) {
    if (N == 1) 
        printf("Move disk 1 from pin %d to pin %d\n", i, k);
    else {
        int tmp = 6 - i - k;
        hanoi(N-1, i, tmp);
        printf("Move disk %d from pin %d to pin %d\n", N, i, k);
        hanoi(N-1, tmp, k);
    }
}

void generate_instructions(int N) {
    hanoi(N, 1, 2); // будем перемещать диски с первого штыря на второй
}

int main() {
    int N;
    std::cin >> N;

    generate_instructions(N);
}