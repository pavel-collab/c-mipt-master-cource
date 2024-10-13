#include <iostream>

#include "Container.hpp"

int main() {
    MyVector::Container my_vector(5);
    my_vector.push_back(1);
    my_vector.push_back(2);
    my_vector.push_back(3);
    my_vector.push_back(4);
    my_vector.push_back(5);
    my_vector.push_back(6);

    std::cout << my_vector.size() << std::endl;
    std::cout << my_vector.capacity() << std::endl;

    for (int i = 0; i < my_vector.size(); i++) {
        printf("my_vector[%d] = %d\n", i, my_vector[i]);
    }

    // MyVector::Container old_container(10);
    // MyVector::Container new_container_copy; 
    // MyVector::Container new_container_move; 

    // /* now objects exist */

    // new_container_copy = old_container;
    // new_container_move = std::move(old_container); // now old container lost his initial consition

    return 0;
}