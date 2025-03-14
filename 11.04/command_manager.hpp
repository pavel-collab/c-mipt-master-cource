#pragma once

#include "command_intefrece.hpp"

#include <vector>
#include <memory>

//TODO: write a comments to class
//TODO: refactor names
//TODO: refactor code style

class CommandManager {
    private:
        std::vector<std::unique_ptr<Command>> history;
    public:
        void executeCommand(std::unique_ptr<Command> command) {
            command->execute();
            history.push_back(std::move(command));
        }
    
        void undo() {
            if (!history.empty()) {
                history.back()->undo();
                history.pop_back();
            }
        }
    };