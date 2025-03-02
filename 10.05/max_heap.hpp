#ifndef _MAX_HEAP_H
#define _MAX_HEAP_H


#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class MaxHeap {
public:
    MaxHeap() {}

    // Insert a new element into the heap
    void insert(T key) {
        heap.push_back(key);
        siftUp(heap.size() - 1);
    }

    // Extract the maximum element from the heap
    T extractMax() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        T maxElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return maxElement;
    }

    // Get the maximum element without removing it
    T getMax() const {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Get the size of the heap
    size_t size() const {
        return heap.size();
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return heap.empty();
    }

private:
    std::vector<T> heap;

    // Sift up the element at index i
    void siftUp(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (heap[i] <= heap[parent]) {
                break;
            }
            std::swap(heap[i], heap[parent]);
            i = parent;
        }
    }

    // Sift down the element at index i
    void siftDown(size_t i) {
        size_t size = heap.size();
        while (true) {
            size_t leftChild = 2 * i + 1;
            size_t rightChild = 2 * i + 2;
            size_t largest = i;

            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }
            if (largest == i) {
                break;
            }
            std::swap(heap[i], heap[largest]);
            i = largest;
        }
    }
};

#endif //_MAX_HEAP_H