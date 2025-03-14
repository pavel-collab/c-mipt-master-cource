#include "commands.hpp"
#include "text_editor.hpp"
#include "command_manager.hpp"

int main() {
    TextEditor editor;
    CommandManager commandManager;

    // Выполняем команды
    commandManager.executeCommand(std::make_unique<WriteCommand>(editor, "Hello"));
    commandManager.executeCommand(std::make_unique<WriteCommand>(editor, ", World!"));
    
    // Отменяем последнюю команду
    commandManager.undo();

    // Выполняем команду удаления
    commandManager.executeCommand(std::make_unique<EraseCommand>(editor, 6));
    
    // Отменяем удаление (но в данном примере оно не реализовано)
    commandManager.undo();

    return 0;
}