#include <iostream>
#include <string>

#include "logger.hpp"

int main() {
    logger::Logger logger("log.txt");  // Создаем объект Logger, который открывает файл

    logger.log("Starting the program");

    // // Копируем логгер
    // logger::Logger logger_copy = logger;
    // logger_copy.log("This is a log message from logger_copy");

    // Перемещаем логгер
    logger::Logger logger_moved = std::move(logger);
    logger_moved.log("This is a log message from logger_moved");

    // Выход из программы, деструктор Logger будет вызван автоматически
    return 0;
}