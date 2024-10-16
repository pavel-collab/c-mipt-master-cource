#include <iostream>
#include <vector>
#include <deque>

template <typename T, typename C = std::vector<T>>
void multiple_push_back(C& container, T arg)
{
    container.push_back(arg);
}

template <typename T, typename C = std::vector<T>, typename ... Ts>
void multiple_push_back(C& container, T arg0, Ts ... args)
{
    multiple_push_back(container, arg0);
    multiple_push_back(container, args...);
}

int main() {
    std::vector<int> vec;
    std::deque<char> deq;

    multiple_push_back(vec, 1, 2, 3, 4, 5);
    multiple_push_back(deq, 'a', 'b', 'c', 'd');

    for (auto el : vec)
        std::cout << el << " ";
    std::cout << std::endl;

    while(!deq.empty())
    {
        std::cout << deq.front() << " ";
        deq.pop_front();
    }
    std::cout << std::endl;
}