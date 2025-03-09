#pragma once

#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>

//! Yes we know it's not good, but in this case we're using namespace to 
//! simplify source code
using namespace boost::multi_index;

// Структура для хранения записи телефонного справочника
struct Entry {
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;

    Entry(const std::string& ln, const std::string& fn, const std::string& pn)
        : lastName(ln), firstName(fn), phoneNumber(pn) {}
};

// Определяем контейнер с тремя индексами
typedef multi_index_container<
    Entry,
    indexed_by<
        ordered_unique<member<Entry, std::string, &Entry::lastName>>, // Индекс по фамилии
        ordered_non_unique<member<Entry, std::string, &Entry::firstName>>, // Индекс по имени
        ordered_unique<member<Entry, std::string, &Entry::phoneNumber>> // Индекс по номеру телефона
    >
> PhonebookContainer;

class Phonebook {
public:
    void addEntry(const std::string& lastName, const std::string& firstName, const std::string& phoneNumber) {
        entries.emplace(lastName, firstName, phoneNumber);
    }

    void printByLastName() {
        auto& lastNameIndex = entries.get<0>();
        for (const auto& entry : lastNameIndex) {
            std::cout << entry.lastName << ", " << entry.firstName << ": " << entry.phoneNumber << std::endl;
        }
    }

    void printByFirstName() {
        auto& firstNameIndex = entries.get<1>();
        for (const auto& entry : firstNameIndex) {
            std::cout << entry.firstName << ", " << entry.lastName << ": " << entry.phoneNumber << std::endl;
        }
    }

    void findByPhoneNumber(const std::string& phoneNumber) {
        auto& phoneIndex = entries.get<2>();
        auto it = phoneIndex.find(phoneNumber);
        if (it != phoneIndex.end()) {
            std::cout << "Entry found: " << it->lastName << ", " << it->firstName << ": " << it->phoneNumber << std::endl;
        } else {
            std::cout << "Entry not found for phone number: " << phoneNumber << std::endl;
        }
    }

private:
    PhonebookContainer entries; // Контейнер для хранения записей
};