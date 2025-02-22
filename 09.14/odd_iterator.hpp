#ifndef _ODD_ITERATOR_H_
#define _ODD_ITERATOR_H_

namespace odd_iterator {
class OddGenerator {
public:
    OddGenerator(int start, int end)
        : start_number(start % 2 == 0 ? start + 1 : start)
        , end_number(end)
    {
    }

    class iterator {
    public:
        explicit iterator(int current)
            : current_value(current)
        {
        }

        int operator*() const
        {
            return current_value;
        }

        iterator& operator++()
        {
            current_value += 2;
            return *this;
        }

        bool operator!=(const iterator& other) const
        {
            return current_value != other.current_value;
        }

    private:
        int current_value;
    };

    iterator begin() const
    {
        return iterator(start_number);
    }

    iterator end() const
    {
        return iterator(end_number + 2);
    }

private:
    int start_number;
    int end_number;
};
}

#endif //_ODD_ITERATOR_H_