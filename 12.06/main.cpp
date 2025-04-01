#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>

bool is_separator(char ch)
{
    static std::unordered_set<char> separators = {' ', '\n', '\t', ';'};

    return separators.find(ch) != separators.end();
}

std::string capitalize_words(const std::string& str)
{
    std::string result;
    bool new_word = true;

    for (char ch : str)
    {
        if (is_separator(ch))
        {
            result += ch;
            new_word = true;
        }
        else
        {
            if (new_word)
            {
                result += std::toupper(ch);
                new_word = false;
            }
            else
                result += std::tolower(ch);
        }
    }

    return result;
}

int main()
{
    std::string text = "heLLo, \twoRLD\nwelcome to the world;heNCe$, we are free to work with ';' sign";
    std::string result = capitalize_words(text);

    std::cout << "Original text: " << text << std::endl;
    std::cout << "Formatted text: " << result << std::endl;

    return 0;
}


