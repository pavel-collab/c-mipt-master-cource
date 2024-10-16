#include <iostream>
#include <vector>

/* Doesn't remove duplicates, just move it to the end of the vector. */
template <typename T>
size_t not_std_uqiue(std::vector<T>& vec, size_t first, size_t last) {
    if (first == last)
        return last;

    size_t result = first;
    while (++first != last) {
        if (!(vec[result] == vec[first]) && ++result != first) { 
            auto tmp = vec[first];
            vec[first] = vec[result];
            vec[result] = tmp;
        }
    }
 
    return ++result;
}

int main() {
    std::vector<int> int_vec = {1, 4, 9, 9, 0, 0, 0, 12, 13, 13, 14};
    std::vector<char> char_vec = {'a', 'a', 'a', 'g', 'd', 'd', 'w', 'q', 'q', 'q', 'v'};
    std::vector<float> float_vec = {12.98, 12.98, 12.98, 12.98, 12.0, 12.01, 12.01, 12.1, 12.2};

    auto last1 = not_std_uqiue(int_vec, 0, int_vec.size());
    for (auto i = 0; i < last1; i++) 
        std::cout << int_vec[i] << " ";
    std::cout << std::endl;

    auto last2 = not_std_uqiue(char_vec, 0, char_vec.size());
    for (auto i = 0; i < last2; i++) 
        std::cout << char_vec[i] << " ";
    std::cout << std::endl;

    auto last3 = not_std_uqiue(float_vec, 0, float_vec.size());
    for (auto i = 0; i < last3; i++) 
        std::cout << float_vec[i] << " ";
    std::cout << std::endl;
}