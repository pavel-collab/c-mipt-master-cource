#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <typename Iterator>
std::string concatenate_with_separator(Iterator begin, Iterator end, 
                                       const std::string& separator)
{
    std::string result;

    if (begin != end)
    {
        result += *begin;
        ++begin;

        while (begin != end)
        {
            result += separator;
            result += *begin;
            ++begin;
        }
    }

    return result;
}

int main()
{
    std::vector<std::string> strings = {"/home", "dfrolov", "cpp_masters_course", "second_sem", __FILE__};
    std::string separator = "/";

    std::string result = concatenate_with_separator(
        strings.begin(), strings.end(), separator);
    std::cout << "Concatenated string: " << result << std::endl;

    return 0;
}


