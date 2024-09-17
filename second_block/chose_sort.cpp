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

    size_t slow_idx = 0;
    size_t fast_idx = 0;
    size_t min_idx;

    while (slow_idx < v.size()) {
        min_idx = slow_idx;
        fast_idx = slow_idx + 1;

        while (fast_idx < v.size()) {
            if (v[fast_idx] < v[min_idx])
                min_idx = fast_idx;
            fast_idx++;
        }

        if (min_idx != slow_idx) 
            std::iter_swap(v.begin() + slow_idx, v.begin() + min_idx);
        slow_idx++;
    }

    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}