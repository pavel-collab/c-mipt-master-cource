#pragma once

#include "command_intefrece.hpp"
#include "text_editor.hpp"

#include <iostream>

//TODO: write a comments to class
//TODO: refactor names
//TODO: refactor code style

// Конкретная команда для добавления текста
class WriteCommand : public Command {
private:
    TextEditor& editor;
    std::string textToWrite;
public:
    WriteCommand(TextEditor& editor, const std::string& text)
        : editor(editor), textToWrite(text) {}

    void execute() override {
        editor.write(textToWrite);
    }

    void undo() override {
        editor.erase(textToWrite.length());
    }
};
    
// Конкретная команда для удаления текста
class EraseCommand : public Command {
private:
    TextEditor& editor;
    size_t length;
public:
    EraseCommand(TextEditor& editor, size_t length)
        : editor(editor), length(length) {}

    void execute() override {
        editor.erase(length);
    }

    void undo() override {
        // Для упрощения не реализуем восстановление удаленного текста
        std::cerr << "Нет возможности отмены удаления" << std::endl;
    }
};
    