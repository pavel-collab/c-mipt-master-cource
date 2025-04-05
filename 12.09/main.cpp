#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cassert>

class RLECodec {
public:
    // Классическое RLE-кодирование
    std::string encode_classic(const std::string& data) {
        if (data.empty()) {
            return "";
        }

        std::string result;
        int count = 1;
        char current_char = data[0];

        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i] == current_char) {
                count++;
            } else {
                result += std::to_string(count) + current_char;
                current_char = data[i];
                count = 1;
            }
        }

        result += std::to_string(count) + current_char;
        return result;
    }

    // Декодирование классического RLE
    std::string decode_classic(const std::string& encoded_data) {
        if (encoded_data.empty()) {
            return "";
        }

        std::string result;
        size_t i = 0;

        while (i < encoded_data.size()) {
            // Считываем количество повторений
            std::string count_str;
            while (std::isdigit(encoded_data[i])) {
                count_str += encoded_data[i];
                ++i;
            }

            // Получаем символ и добавляем его нужное количество раз
            char char_ = encoded_data[i];
            int count = std::stoi(count_str);
            result.append(count, char_);
            ++i;
        }

        return result;
    }

    // Оптимизированное RLE-кодирование
    std::string encode_optimized(const std::string& data) {
        if (data.empty()) {
            return "";
        }

        std::string result;
        int count = 1;
        char current_char = data[0];

        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i] == current_char) {
                count++;
            } else {
                if (count > 1) {
                    result += current_char + std::to_string(count);
                } else {
                    result += current_char;
                }
                current_char = data[i];
                count = 1;
            }
        }

        if (count > 1) {
            result += current_char + std::to_string(count);
        } else {
            result += current_char;
        }

        return result;
    }

    // Декодирование оптимизированного RLE
    std::string decode_optimized(const std::string& encoded_data) {
        if (encoded_data.empty()) {
            return "";
        }

        std::string result;
        size_t i = 0;

        while (i < encoded_data.size()) {
            char char_ = encoded_data[i];
            ++i;

            // Проверяем, есть ли после символа число
            std::string count_str;
            while (i < encoded_data.size() && std::isdigit(encoded_data[i])) {
                count_str += encoded_data[i];
                ++i;
            }

            // Если число есть, повторяем символ указанное количество раз
            // Если нет, добавляем символ один раз
            if (!count_str.empty()) {
                int count = std::stoi(count_str);
                result.append(count, char_);
            } else {
                result += char_;
            }
        }

        return result;
    }
};

// Примеры использования
int main() {
    // Создаем экземпляр класса
    RLECodec codec;

    // Пример 1: Классическое RLE-кодирование
    std::cout << "=== Классическое RLE ===" << std::endl;
    std::string original = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB";
    std::string encoded = codec.encode_classic(original);
    std::string decoded = codec.decode_classic(encoded);
    assert(original == decoded);
    std::cout << "Исходная строка:    " << original << std::endl;
    std::cout << "Закодированная:     " << encoded << std::endl;
    std::cout << "Декодированная:     " << decoded << std::endl;
    std::cout << "Степень сжатия:     " << static_cast<double>(original.size()) / encoded.size() << std::endl;

    // Пример 2: Оптимизированное RLE-кодирование
    std::cout << "\n=== Оптимизированное RLE ===" << std::endl;
    original = "AABBBCCCCDDDDAAAAA";
    encoded = codec.encode_optimized(original);
    decoded = codec.decode_optimized(encoded);
    assert(original == decoded);
    std::cout << "Исходная строка:    " << original << std::endl;
    std::cout << "Закодированная:     " << encoded << std::endl;
    std::cout << "Декодированная:     " << decoded << std::endl;
    std::cout << "Степень сжатия:     " << static_cast<double>(original.size()) / encoded.size() << std::endl;
}