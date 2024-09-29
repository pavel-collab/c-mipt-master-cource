#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    int N, tmp;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> tmp;
        v.emplace_back(tmp);
    }

    for (size_t i = 0; i < size_t(v.size() / 2); i++) {
        std::swap(v[i], v[v.size() - i - 1]);
    }

    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}