#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N; // N is a number of PAIRS

    if (N == 0)
        std::cout << 0 << std::endl;
        return 0;

    if (N == 1)
        std::cout << 1 << std::endl;
        return 0;

    std::vector<unsigned long long> save(N+1, 0);
    save[1] = 1;

    // use dynamic programming

    return 0;
}