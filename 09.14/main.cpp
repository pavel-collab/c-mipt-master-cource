#include <iostream>

//TODO: move iterator to hpp file, refactor names

class odd_number_generator
{
public:
    odd_number_generator(int start, int end)
        : start_number(start % 2 == 0 ? start + 1 : start), end_number(end) {}

    class iterator {
    public:
        explicit iterator(int current) : current_value(current) {}

        int operator* () const
        {
            return current_value;
        }

        iterator& operator++ ()
        {
            current_value += 2;
            return *this;
        }

        bool operator!= (const iterator& other) const
        {
            return current_value != other.current_value;
        }

    private:
        int current_value;
    };

    iterator begin () const
    {
        return iterator (start_number);
    }

    iterator end () const
    {
        return iterator (end_number + 2);
    }

private:
    int start_number;
    int end_number;
};

int main () {
    odd_number_generator range(1, 19);

    for (int num : range)
        std::cout << num << " ";

    return 0;
}

