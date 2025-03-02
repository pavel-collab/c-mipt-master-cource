#include "max_heap.hpp"
#include <iostream>

int main() {
    MaxHeap<int> maxHeap;

    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);
    maxHeap.insert(15);

    std::cout << "Max element: " << maxHeap.getMax() << std::endl; // Should output 30

    std::cout << "Extracting max: " << maxHeap.extractMax() << std::endl; // Should output 30
    std::cout << "New max element: " << maxHeap.getMax() << std::endl; // Should output 20

    return 0;
}