#include <iostream>
#include <vector>
#include <map>

/*

Мы, конечно, могли бы для решения данной задачи написать свою кучу
с блэкджеком и пивом "Гинес", но написание собственной реализации той или 
иной структуры данных (мы, конечно, имеем ввиду хорошее написание) это экстрим.
Поэтому, если есть что-то предусмотренное стандартом -- лучше испольовать его.

В стандарте у нас есть замечательная структура std::map (которую используют раз в 10000 лет),
которая в подкапотной реализации представляет собой красно-черное дерево, а по
интерфейсу использования как раз может считаться за min кучу.

Построение кучи из неотсортированного массива O(n)
Извлечение одного элемента из кучи O(log n), так как при каждом извлечении кучу необходимо перестраивать
Таким образом, извлечение всех элементов из кучи O(n lon n)
Результирующая сложность вместе с построением O(n) + O(n lon n) = O(n lon n)

*/

template <typename T>
void heap_sort(std::vector<T> &vec)
{
    std::map<T, int> heap;
    for (size_t i = 0; i < vec.size(); i++) {
        heap.insert(std::pair<T, int>(vec[i], i));
    }

    size_t idx = 0;
    for (auto it = heap.begin(); it != heap.end(); it++)
        vec[idx++] = it->first;
}

int main() {
    std::vector<int> int_vec = {5, 7, 34, 0, 0, -32, 17};
    std::vector<char> char_vec = {'g', 'f', 'a', 'p', 'b', 'v', 'c'};
    std::vector<float> float_vec = {12.98, 12.0, 12.01, 12.1, 12.2};

    heap_sort<int>(int_vec);
    for (auto el : int_vec)
        std::cout << el << " ";
    std::cout << std::endl;

    heap_sort<char>(char_vec);
    for (auto el : char_vec)
        std::cout << el << " ";
    std::cout << std::endl;

    heap_sort<float>(float_vec);
    for (auto el : float_vec)
        std::cout << el << " ";
    std::cout << std::endl;
}