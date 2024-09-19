#include <iostream>
#include <vector>

/* Doesn't remove duplicates, just move it to the end of the vector. */
size_t not_std_uqiue(std::vector<int> *vec, size_t first, size_t last) {
    if (first == last)
        return last;

    size_t result = first;
    while (++first != last) {
        if (!((*vec)[result] == (*vec)[first]) && ++result != first) { 
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

    /*
    Note, that here it's important to put the original size of the vector
    not the last vector index, that is size - 1.
    In the original implementation with iterators last is a vector.end() that points 
    to the position after end.

                  last
                   |
                   V
    1 2 3 4 5 6 7 [ ] 
    */
    auto last = not_std_uqiue(&v, 0, v.size());
    
    std::cout << "removed duplicates:" << std::endl;
    for (size_t i = 0; i < last; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "full vector:" << std::endl;
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}