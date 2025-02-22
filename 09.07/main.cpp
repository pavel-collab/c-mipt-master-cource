#include <iostream>

#include "binary_tree.hpp"

int main() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);

    std::cout << "In-order traversal: ";
    tree.inorderTraversal();

    return 0;
}