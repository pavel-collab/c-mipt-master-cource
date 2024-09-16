#include <iostream>
#include <vector>
#include <algorithm>

void shell_sort(std::vector<int>* v, int gap) {
    int current_position = gap;

    while (current_position < v->size()) {
        if ((*v)[current_position] < (*v)[current_position - gap]) {
            int factor = 1;
            while ((current_position - factor*gap >= 0) && ((*v)[current_position] < (*v)[current_position - factor*gap])) {
                factor += 1;
            }
            std::iter_swap(v->begin() + current_position, v->begin() + current_position - (factor-1)*gap);
        }
        current_position += 1;
    }

    if (gap < 2)
        return;
    else
        shell_sort(v, int(gap / 2));
}

int main() {
    std::vector<int> v;
    int N, tmp;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> tmp;
        v.emplace_back(tmp);
    }

    shell_sort(&v, int(v.size() / 2));

    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}