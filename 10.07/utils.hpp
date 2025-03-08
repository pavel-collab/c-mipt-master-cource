#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

void umap2file(std::unordered_map<unsigned int, unsigned int>& hash_distribution, 
               const char* file_name)
{    
    std::fstream outputFile;
    outputFile.open(file_name, std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "[err] can't open file " << file_name << std::endl;
        return; 
    }

    outputFile << "values,hits" << std::endl;
    for (const auto& pair : hash_distribution) {
        outputFile << pair.first << "," << pair.second << std::endl;
    }

    outputFile.close();
}

void collisions2file(std::unordered_map<std::string, unsigned int> hash_collisions, const char* file_name)
{   
    std::fstream outputFile;
    outputFile.open(file_name, std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "[err] can't open file " << file_name << std::endl;
        return; 
    }

    outputFile << "hashes,collisions" << std::endl;
    for (const auto& pair : hash_collisions) {
        outputFile << pair.first << "," << pair.second << std::endl;
    }

    outputFile.close();
}