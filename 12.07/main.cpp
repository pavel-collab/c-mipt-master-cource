#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <cctype> // Для функции isalpha

template <typename Iterator>
std::string concat(Iterator begin, Iterator end, const std::string& sep)
{
    std::ostringstream oss;
    
    if (begin != end)
    {
        oss << *begin;
        ++begin;

        while (begin != end)
        {
            if (std::isalpha(*begin))
            {
                oss << sep;
            }
            oss << *begin;
            ++begin;
        }
    }

    return oss.str();
}

int main()
{
    std::vector<std::string> strings = {"one", "two", "three", "42"};
    std::string separator = "*";

    std::string result = concat(
        strings.begin(), strings.end(), separator);
    std::cout << "Result: " << result << std::endl;

    return 0;
}