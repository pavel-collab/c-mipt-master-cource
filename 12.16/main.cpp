#include <iostream>
#include <regex>
#include <string>

//TODO: make a option to enter url from command line or read it from file
//TODO: test the generator for url addresses

int main() {
    std::string url;
    std::cout << "Enter the URL: ";
    std::getline(std::cin, url);

    // Обновлённое регулярное выражение для полного разбора URL
    const std::regex url_regex(
        R"((https?)://([^/:?#]+)(?::(\d+))?(\/[^\s?#]*)?(?:\?([^#\s]*))?(?:#(\S+))?)",
        std::regex::ECMAScript
    );

    std::smatch match;
    if (std::regex_match(url, match, url_regex)) {
        std::cout << "Protocol:  " << match[1] << '\n';
        std::cout << "Domen:     " << match[2] << '\n';
        std::cout << "Port:      " << (match[3].matched ? match[3].str() : "by default") << '\n';
        std::cout << "Path:      " << (match[4].matched ? match[4].str() : "/") << '\n';
        std::cout << "Query:     " << (match[5].matched ? match[5].str() : "no such") << '\n';
        std::cout << "Fragment:  " << (match[6].matched ? match[6].str() : "no such") << '\n';
    } else {
        std::cout << "[err] incorrect URL.\n";
    }

    return 0;
}