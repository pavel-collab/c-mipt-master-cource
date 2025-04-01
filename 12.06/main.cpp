#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>

bool is_separator(char ch)
{
    static std::unordered_set<char> separators = {' ', '\n', '\t', ';', '.', ',', '!', '?', ':', '-', '/', '\\', '(', ')', '[', ']', '{', '}', '<', '>', '@', '#', '$', '%', '^', '&', '*', '~', '`', '+', '=', '|', '"', '\''};
    return separators.find(ch) != separators.end();
}

std::string process_scentence(const std::string& str)
{
    std::string res;
    bool next_word = true;

    for (char ch : str)
    {
        if (is_separator(ch))
        {
            res += ch;
            next_word = true;
        }
        else
        {
            if (next_word)
            {
                res += std::toupper(ch);
                next_word = false;
            }
            else
                res += std::tolower(ch);
        }
    }

    return res;
}

int main()
{
    std::string text = "привет, мир\nдобро пожаловать в мир; вот так, мы можем работать с ';' символом";
    std::string result = process_scentence(text);

    std::cout << "Исходный текст: " << text << std::endl;
    std::cout << "Отформатированный текст: " << result << std::endl;

    return 0;
}