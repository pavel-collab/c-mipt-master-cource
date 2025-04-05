#include <iostream>
#include <string>
#include <regex>

int main() {
    // Сырой текст с валидными и невалидными email и мусором
    const std::string text = R"(
        Email examples: vd;lsdsvv
        valid.email@example.com sdvvv
        vsdsdvdv
        another.valid_email123@sub.domain.org ksdvs
        invalid.@mail.com
        sdvsdv
        @nouser.com
        plainaddress
        user@.invalid.com
        sdvasdv
        garbage@@example..com
        good.one+tag@gmail.com
        sdvp[[[[[[[]]]]]]]
    )";

    // Упрощённое регулярное выражение для email
    const std::regex email_regex(R"((\b[\w.+-]+@[a-zA-Z\d-]+(\.[a-zA-Z\d-]+)+\b))");

    std::sregex_iterator begin(text.begin(), text.end(), email_regex);
    std::sregex_iterator end;

    std::cout << "Correct emails:\n";
    for (auto it = begin; it != end; ++it) {
        std::cout << " - " << it->str() << '\n';
    }

    return 0;
}