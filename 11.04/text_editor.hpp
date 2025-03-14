#pragma once

#include <iostream>
#include <string>

//TODO: write a comments to class
//TODO: refactor names
//TODO: refactor code style

class TextEditor {
private:
    std::string text;
public:
    void write(const std::string& newText) {
        text += newText;
        std::cout << "Текущий текст: " << text << std::endl;
    }

    void erase(size_t length) {
        if (length > text.length()) length = text.length();
        text.erase(text.length() - length);
        std::cout << "Текущий текст после удаления: " << text << std::endl;
    }

    std::string getText() const {
        return text;
    }
};