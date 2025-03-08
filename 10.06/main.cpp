#include <iostream>
#include <map>

/*
 * std::map assumes that element in it's internal structure are ordered,
 * after changing the value of the key, we don't order internal map
 * structure by hand, in other workds we crash internal invariants.
 * It can lead to undefinded behaviour during insertion, deleting or funding some element.
*/
void unsafe_example()
{
    std::map<int, std::string> m = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    std::cout << "Before changing key" << std::endl;
    for (const auto el : m)
        std::cout << el.first << " : " << el.second << std::endl;
    std::cout << std::endl;

    auto iter = m.find(2);
    if (iter != m.end())
    {   
        int* key_p = const_cast<int*>(&iter->first);
        *key_p = 5;
    }

    std::cout << "After changing key" << std::endl;
    for (const auto el : m)
        std::cout << el.first << " : " << el.second << std::endl;
}

/*
 * In this case we move out the whole node from the std::map,
 * chane it's key and insert back. We use interface methods of
 * std::map, so data structure is looking for it's internal
 * invariants by itself.
*/
void safe_example()
{
    std::map<int, std::string> m = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    std::cout << "Before changing key" << std::endl;
    for (const auto el : m)
        std::cout << el.first << " : " << el.second << std::endl;
    std::cout << std::endl;

    auto node = m.extract(2);
    if (!node.empty())
    {
        node.key() = 5;
        m.insert(std::move(node));
    }   

    std::cout << "After changing key" << std::endl;
    for (const auto el : m)
        std::cout << el.first << " : " << el.second << std::endl;
}

int main() {

#if SAFE==1
    safe_example();
#endif

#if UNSAFE==1
    unsafe_example();
#endif

}