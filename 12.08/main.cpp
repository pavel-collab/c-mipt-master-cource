#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

// Функция для разбиения строки на слова
std::vector<std::string> split_string(const std::string& str, const std::vector<char>& separators) {
    std::vector<std::string> tokens;
    std::string cur_token;

    for (char ch : str) {
        if (std::find(separators.begin(), separators.end(), ch) != separators.end()) {
            if (!cur_token.empty()) {
                tokens.push_back(cur_token);
                cur_token.clear();
            }
        } else {
            cur_token += ch;
        }
    }

    if (!cur_token.empty()) {
        tokens.push_back(cur_token);
    }

    return tokens;
}

int main() {
    std::string str = "We are; glad to > see you > > on our;;today c++:meetup!";
    std::vector<char> separators = {'>', ':', ';', ' '};

    std::vector<std::string> tokens = split_string(str, separators);

    std::cout << "Original string: " << str << std::endl;
    for (const auto& token : tokens) {
        std::cout << "\ttoken: " << token << std::endl;
    }

    return 0;
}