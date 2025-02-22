#include "odd_iterator.hpp"
#include <iostream>

int main()
{
    odd_iterator::OddGenerator range(1, 19);

    for (int num : range)
        std::cout << num << " ";

    return 0;
}
