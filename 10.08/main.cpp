#include "phone_book.hpp"

#include <iostream>
#include <string>

int main() {
    Phonebook phonebook;

    // Добавление записей
    phonebook.addEntry("Smith", "John", "123456789");
    phonebook.addEntry("Doe", "Jane", "987654321");
    phonebook.addEntry("Brown", "Charlie", "555555555");

    // Печать записей по фамилии
    std::cout << "Entries sorted by last name:" << std::endl;
    phonebook.printByLastName();
    
    // Печать записей по имени
    std::cout << "\nEntries sorted by first name:" << std::endl;
    phonebook.printByFirstName();

    // Поиск по номеру телефона
    std::cout << "\nSearching for phone number 123456789:" << std::endl;
    phonebook.findByPhoneNumber("123456789");

    return 0;
}