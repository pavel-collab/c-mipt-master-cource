#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <experimental/source_location>
#include <fstream>
#include <iostream>

namespace logger {

class Logger final {
public:
    Logger(const std::string& filename, const std::source_location location = std::source_location::current())
        : log_file(filename, std::ios::app), filename(filename)
    { // Открываем файл для записи
        if (!log_file.is_open()) {
            std::cerr << "Failed to open log file: " << filename
                      << " [" << location.file_name() << ":"
                      << location.line() << "]" << std::endl;
        } else {
            log_file << "Logger initialized in " << location.file_name() << ":"
                     << location.line() << std::endl;
        }
    }

    //! There are some troubles with copy constructor and copy 
    //TODO: Write correct copy constructor and copy assignment or prove, that in this implementation it is incorrect

    // Move конструктор
    Logger(Logger&& other) noexcept
        : log_file(std::move(other.log_file))
    {
        other.log_file.clear(); // Очищаем состояние перемещаемого объекта
    }

    // Оператор присваивания перемещением
    Logger& operator=(Logger&& other) noexcept
    {
        if (this != &other) {
            if (log_file.is_open()) {
                log_file.close(); // Закрываем текущий файл
            }
            log_file = std::move(other.log_file);
            other.log_file.clear(); // Очищаем состояние перемещаемого объекта
        }
        return *this;
    }

    ~Logger()
    {
        if (log_file.is_open()) {
            log_file << "Logger destroyed" << std::endl;
            log_file.close(); // Освобождаем ресурс
        }
    }

    //? What about single responsibility? Do I need to write this method out of the class?
    void log(const std::string& message,
        const std::source_location location = std::source_location::current())
    {
        if (log_file.is_open()) {
            log_file << "[" << location.file_name() << ":"
                     << location.line() << " "
                     << location.column() << "] "
                     << message << std::endl;
        }
    }

private:
    std::ofstream log_file; // Ресурс для логирования
    std::string filename; //??? Будем хранить в классе имя файла, иначе проблемы с копированием
};
}

#endif // _LOGGER_H_