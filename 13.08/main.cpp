#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Рекурсивный сбор путей файлов и директорий
void collect_paths(const std::string& dir, std::vector<std::string>& paths) {
    DIR* dp = opendir(dir.c_str());
    if (!dp) return;

    struct dirent* entry;
    while ((entry = readdir(dp)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string full_path = dir + "/" + name;
        paths.push_back(full_path);

        struct stat stat_buf;
        if (stat(full_path.c_str(), &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode)) {
            collect_paths(full_path, paths);
        }
    }
    closedir(dp);
}

// Удаление файла или директории
bool remove_path(const std::string& path) {
    struct stat stat_buf;
    if (lstat(path.c_str(), &stat_buf) != 0) return false;

    if (S_ISDIR(stat_buf.st_mode)) {
        DIR* dp = opendir(path.c_str());
        if (!dp) return false;

        struct dirent* entry;
        while ((entry = readdir(dp)) != nullptr) {
            std::string name = entry->d_name;
            if (name != "." && name != "..") {
                remove_path(path + "/" + name);
            }
        }
        closedir(dp);
        return rmdir(path.c_str()) == 0;
    }
    return unlink(path.c_str()) == 0;
}

// Парсинг времени из строки
time_t parse_cutoff_time(const std::string& time_str) {
    std::tm tm = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::runtime_error("Invalid time format");
    }
    return mktime(&tm);
}

int main() {
    std::string dir_path;
    std::cout << "Enter directory path: ";
    std::cin >> dir_path;

    std::string time_str;
    std::cout << "Enter cutoff time (YYYY-MM-DD HH:MM:SS): ";
    std::cin >> time_str;

    try {
        time_t cutoff_time = parse_cutoff_time(time_str);
        std::vector<std::string> paths;
        collect_paths(dir_path, paths);

        // Сортировка по убыванию длины пути
        std::sort(paths.begin(), paths.end(),
            [](const std::string& a, const std::string& b) {
                return a.length() > b.length();
            });

        for (const auto& path : paths) {
            struct stat stat_buf;
            if (lstat(path.c_str(), &stat_buf) != 0) continue;

            if (stat_buf.st_mtime < cutoff_time) {
                if (remove_path(path)) {
                    std::cout << "Removed: " << path << '\n';
                } else {
                    std::cerr << "Error removing: " << path << '\n';
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}