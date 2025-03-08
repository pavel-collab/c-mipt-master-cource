#pragma once

#include <cstdlib> // Для rand() и srand()
#include <ctime> // Для time()
#include <string>

namespace string_generator {

std::string generateRandomString(int length)
{
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";
    std::string result;
    result.reserve(length); // Резервируем память для строки

    for (int i = 0; i < length; ++i) {
        int index = rand() % characters.size(); // Генерация случайного индекса
        result += characters[index]; // Добавляем символ в строку
    }

    return result;
}

}