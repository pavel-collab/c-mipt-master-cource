#include <iostream>
#include <list>

/*
Для нахождения середины списка используем метод быстрого и медленного указателя.
С головы списка запускаем 2 указателя: медленный за раз шагает на 1 шаг, быстрый на 2,
когда быстрый достигнет конца списка, медленный будет указывать ровно на середину.
*/

int main() {
    std::list<int> test_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto slow_pointer = test_list.begin();
    auto fast_pointer = test_list.begin();

    while (fast_pointer != test_list.end()) {
        fast_pointer++;
        if (fast_pointer == test_list.end())
            break;
        fast_pointer++;
        slow_pointer++;
    }

    std::cout << "The middle of the list is " << *slow_pointer << std::endl;
}