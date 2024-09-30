#include <iostream>
#include <vector>

// Разделение по схеме Lomuto
int partition(std::vector<int>& vec, int start, int end)
{
    // Выбираем крайний правый элемент в качестве опорного элемента массива
    int pivot = vec[end];

    // элементы, меньшие точки поворота, будут перемещены влево от `pIndex`
    // элементы больше, чем точка поворота, будут сдвинуты вправо от `pIndex`
    // равные элементы могут идти в любом направлении
    int pIndex = start;

    // каждый раз, когда мы находим элемент, меньший или равный опорному, `pIndex`
    // увеличивается, и этот элемент будет помещен перед опорной точкой.
    for (int i = start; i < end; i++)
    {
        if (vec[i] <= pivot)
        {
            std::iter_swap(vec.begin() + i, vec.begin() + pIndex);
            pIndex++;
        }
    }

    // поменять местами `pIndex` с пивотом
    std::iter_swap(vec.begin() + pIndex, vec.begin() + end);

    // вернуть `pIndex` (индекс опорного элемента)
    return pIndex;
}

// Процедура быстрой сортировки
void quicksort(std::vector<int>& vec, int start, int end)
{
    // базовое условие
    if (start >= end) {
        return;
    }

    // переставить элементы по оси
    int pivot = partition(vec, start, end);

    // повторяем подмассив, содержащий элементы, меньшие опорной точки
    quicksort(vec, start, pivot - 1);

    // повторяем подмассив, содержащий элементы, превышающие точку опоры
    quicksort(vec, pivot + 1, end);
}

int main() {
    std::vector<int> v;
    int N, tmp;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> tmp;
        v.emplace_back(tmp);
    }

    quicksort(v, 0, v.size());

    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}