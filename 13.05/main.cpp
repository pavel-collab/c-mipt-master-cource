#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

// Проверка, состоит ли строка только из пробельных символов
bool is_whitespace_line(const string& line) {
    return all_of(line.begin(), line.end(), [](char c) {
        return isspace(static_cast<unsigned char>(c));
    });
}

// Основная функция обработки файла
void clean_file(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Cannot open input file\n";
        return;
    }

    // Создаем временный файл
    string tempname = filename + ".tmp";
    ofstream out(tempname);
    if (!out) {
        cerr << "Error: Cannot create temporary file\n";
        return;
    }

    string line;
    bool has_content = false;
    
    while (getline(in, line)) {
        if (!is_whitespace_line(line)) {
            // Сохраняем оригинальные переводы строк
            if (has_content) out << '\n';
            out << line;
            has_content = true;
        }
    }

    in.close();
    out.close();

    // Заменяем оригинальный файл
    if (remove(filename.c_str()) != 0) {
        cerr << "Error: Failed to remove original file\n";
        return;
    }
    if (rename(tempname.c_str(), filename.c_str()) != 0) {
        cerr << "Error: Failed to rename temporary file\n";
    }
}

int main() {
    cout << "Enter filename to clean: ";
    string filename;
    cin >> filename;

    clean_file(filename);
    cout << "File processing completed.\n";

    return 0;
}