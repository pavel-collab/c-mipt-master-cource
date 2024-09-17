#include <iostream>
#include <vector>

/*
input:
0 1 2 3 4 5 6 7
1 2 3 3 4 5 5 6
expected out:
1 2 3 4 5 6 3 5
*/

//TODO: доделать, пока не работает
size_t not_std_uqiue(std::vector<int> *vec, size_t first, size_t last) {
    if (first == last)
        return last;

    size_t result = first;
    while (++first != last) { // если текущий элемент НЕ предпоследний
        if (!((*vec)[result] == (*vec)[first]) && ++result != first) { // сравниваем текущий и следующий элемент и проверяем, что индекс не один и тот же
            // меняем местами текущий и последний
            auto tmp = (*vec)[first];
            (*vec)[first] = (*vec)[result];
            (*vec)[result] = tmp;
        }
    }
 
    return ++result;
}

int main() {
    std::vector<int> v;
    int N, tmp;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> tmp;
        v.emplace_back(tmp);
    }

    auto last = not_std_uqiue(&v, 0, v.size()-1);
    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}