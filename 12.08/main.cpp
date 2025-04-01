#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

template <typename Iterator>
std::vector<std::string> split_string(const std::string& str, Iterator begin, 
                                      Iterator end)
{
    std::vector<std::string> tokens;
    std::string current_token;

    for (char ch : str)
    {
        if (std::find(begin, end, ch) != end)
        {
            if (!current_token.empty())
            {
                tokens.push_back(current_token);
                current_token.clear();
            }
        }
        else
        {
            current_token += ch;
        }
    }

    if (!current_token.empty())
    {
        tokens.push_back(current_token);
    }

    return tokens;
}

int main()
{
    std::string str = "> [7 PM] file.cc: Wrong format; > another text here;";
    std::vector<char> separators = {'>', ':', ';'};

    std::vector<std::string> tokens = split_string(str, 
        separators.begin(), separators.end());

    std::cout << "Original string: " << str << std::endl;
    for (const auto& token : tokens)
    {
        std::cout << "\ttoken: " << token << std::endl;
    }

    return 0;
}


