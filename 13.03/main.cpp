#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <pwd.h>

namespace fs = std::filesystem;

struct Process {
    std::string name;
    int pid;
    std::string status;
    std::string owner;
};

std::vector<int> get_recent_pids(size_t count) {
    std::vector<int> pids;
    for (const auto& entry : fs::directory_iterator("/proc")) {
        std::string filename = entry.path().filename();
        if (std::all_of(filename.begin(), filename.end(), ::isdigit)) {
            pids.push_back(std::stoi(filename));
        }
    }
    
    std::sort(pids.rbegin(), pids.rend());
    if (pids.size() > count) pids.resize(count);
    return pids;
}

std::string get_user_name(uid_t uid) {
    if (auto* pwd = getpwuid(uid)) {
        return pwd->pw_name;
    }
    return std::to_string(uid);
}

Process get_process_info(int pid) {
    Process proc;
    proc.pid = pid;
    
    std::ifstream status_file("/proc/" + std::to_string(pid) + "/status");
    std::string line;
    
    while (std::getline(status_file, line)) {
        if (line.compare(0, 5, "Name:") == 0) {
            proc.name = line.substr(6);
            proc.name.erase(0, proc.name.find_first_not_of(" \t"));
        } 
        else if (line.compare(0, 6, "State:") == 0) {
            char state = line[7];
            switch(state) {
                case 'R': proc.status = "Running"; break;
                case 'S': proc.status = "Sleeping"; break;
                case 'D': proc.status = "Waiting";  break;
                case 'Z': proc.status = "Zombie";  break;
                case 'T': proc.status = "Stopped"; break;
                default:  proc.status = "Unknown";
            }
        }
        else if (line.compare(0, 4, "Uid:") == 0) {
            std::istringstream iss(line.substr(5));
            uid_t uid;
            iss >> uid;
            proc.owner = get_user_name(uid);
            break;
        }
    }
    
    return proc;
}

// g++ --std=c++17 main.cpp
int main() {
    constexpr int name_width = 20;
    constexpr int pid_width = 8;
    constexpr int status_width = 12;
    constexpr int owner_width = 18;

    // Получаем 5 последних процессов
    auto pids = get_recent_pids(5);
    std::vector<Process> processes;
    
    for (int pid : pids) {
        try {
            processes.push_back(get_process_info(pid));
        } 
        catch (...) {
            // Пропускаем процессы, которые завершились
        }
    }

    // Заголовок таблицы
    std::cout << std::left
              << std::setw(name_width) << "Process Name"
              << std::setw(pid_width) << "PID"
              << std::setw(status_width) << "Status"
              << std::setw(owner_width) << "Owner"
              << "\n" << std::string(58, '-') << "\n";

    // Вывод данных
    for (const auto& proc : processes) {
        std::cout << std::left
                  << std::setw(name_width) << proc.name.substr(0, name_width-1)
                  << std::setw(pid_width) << proc.pid
                  << std::setw(status_width) << proc.status
                  << std::setw(owner_width) << proc.owner
                  << "\n";
    }

    return 0;
}