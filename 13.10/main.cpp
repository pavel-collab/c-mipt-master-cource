#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

int main() {
    // Ввод пути к директории
    std::string dir_str;
    std::cout << "Enter directory path: ";
    std::cin >> dir_str;
    
    const fs::path dir_path{dir_str};
    
    // Проверка существования директории
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
        std::cerr << "Error: Invalid directory path\n";
        return 1;
    }

    try {
        // Сбор всех элементов директории
        std::vector<fs::path> files;
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            files.push_back(entry.path());
        }

        // Обработка каждого файла
        for (const auto& file_path : files) {
            // Преобразование имени файла в нижний регистр
            std::string new_name = file_path.filename().string();
            std::transform(new_name.begin(), new_name.end(), new_name.begin(),
                [](unsigned char c) { return std::tolower(c); });

            // Создание нового пути и переименование
            fs::path new_path = file_path;
            new_path.replace_filename(new_name);
            
            if (file_path != new_path) {
                fs::rename(file_path, new_path);
                std::cout << "Renamed: " << file_path.filename() 
                          << " -> " << new_path.filename() << "\n";
            }
        }
        
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}