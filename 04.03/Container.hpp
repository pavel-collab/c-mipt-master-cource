/*
 * In the theory work more optimal than #ifndef + #define, cz
 * compiler firstly insert content of included file and only
 * after that check define. On the other hand, #ifndef + #define
 * is more stable (old compilers don't support pragme once) and
 * I found information in the Internet, that modern compilers
 * are able to detect #ifndef + #define and optimise it.
 * Anyway, it doesn't influence to the program inference time,
 * only to compilation time.
 */
#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <cstring>

namespace MyVector 
{  
    template <typename T>
    class Container
    {
    public:

        Container() : m_data(nullptr), m_size(0), m_capacity(0)
        {
            std::cout << "Container::Container (agregate initialisation)" << std::endl;
        }

        Container(std::size_t capacity) : m_size(0), m_capacity(capacity)
        {
            std::cout << "Container::Container (default initialisation)" << std::endl;

            m_data = new T[m_capacity]{};
            assert(m_data != nullptr);
        }

        // copy constructor
        Container(const Container& other) : m_size(other.m_size), m_capacity(other.m_capacity) 
        {
            std::cout << "Container::Container (copy)" << std::endl;

            m_data = new T[m_capacity]{};

            std::copy(other.m_data, other.m_data + m_size, m_data);
        }

        // move constructor
        Container(Container && other) : Container()
        {
            std::cout << "Container::Container (move)" << std::endl;

            swap(other);
        }

        Container & operator=(const Container & other) 
        {
            std::cout << "Container::operator= (copy)" << std::endl;

            if (this != &other)
            {
                auto new_size = other.m_size;

                auto new_data = (new_size ? new T[new_size]{} : nullptr);

                std::copy(other.m_data, other.m_data + m_size, m_data);

                delete[] m_data;

                m_data = new_data;
                m_size = new_size;
            }

            return *this;
        }

        Container & operator=(Container && other) 
        {
            std::cout << "Container::operator= (move)" << std::endl;

            if (this != &other)
            {
                if (m_data) delete[] m_data;
                
                m_data = other.m_data;
                m_size = other.m_size;

                other.m_data = nullptr; other.m_size = 0;
            }

            return *this;
        }

        ~Container()
        {
            std::cout << "Container::~Container" << std::endl;

            delete[] m_data;
        }

        // call for non const object, can modify internal m_data
        T& operator[](const int idx)
        {
            assert(idx >= 0);
            assert(idx < m_capacity);
            return m_data[idx];
        }

        // call for constant objects, only for show internal data
        const T& operator[](const int idx) const
        {
            assert(idx >= 0);
            assert(idx < m_capacity);
            return m_data[idx];
        }

        // call for non const container, let modify the first data cell
        T& front() {
            return m_data[0]; 
        }

        // call for const objects, don't let modify data
        const T& front() const {
            return m_data[0]; 
        }

        // call for non const container, let modify the last data cell
        T& back() {
            return m_data[m_capacity - 1]; 
        }

        // call for const objects, don't let modify data
        const T& back() const {
            return m_data[m_capacity - 1]; 
        }

        const std::size_t size() const { return m_size; }

        const std::size_t capacity() const { return m_capacity; }

        bool empty() const { return m_size == 0 ? true : false; }

        //??????????
        void clear() {
            memset(m_data, 0, sizeof(int)* m_size);
            m_size = 0;
        }

        void push_back(T new_val) {
            if (m_size == m_capacity)
            {
                T* new_data_ptr = new T[m_capacity * 2]{};
                assert(new_data_ptr != nullptr);

                // copy data
                std::memcpy(new_data_ptr, m_data, m_size*sizeof(T));

                // swap pointers
                std::swap(m_data, new_data_ptr);
                m_capacity = m_capacity * 2;

                // free old memory
                delete [] new_data_ptr;
            }  
            m_data[m_size++] = new_val;
        }

    public:

        void swap(Container & other)
        {
            using std::swap; 

            swap(m_data,     other.m_data);
            swap(m_size,     other.m_size);
            swap(m_capacity, other.m_capacity);
        }

    private:

        T* m_data; 
        std::size_t m_size;
        std::size_t m_capacity;

    }; // class Container

    //  ================================================================================================

    template <typename T>
    inline void swap(Container<T> & x, Container<T> & y) { x.swap(y); }

    //  ================================================================================================
}