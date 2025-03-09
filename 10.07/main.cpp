#include "hash_functions.hpp"
#include "string_generator.hpp"
#include "utils.hpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

void process_hash_function(unsigned int (*hash_function)(const char* str, unsigned int length),
    std::unordered_set<std::string>& string_pool,
    std::unordered_map<unsigned int, unsigned int>& hash_distriobution)
{
    for (auto str : string_pool) {
        auto hash = hash_function(str.c_str(), str.length());
        hash_distriobution[hash]++;
    }
}

unsigned int get_collision_number(std::unordered_map<unsigned int, unsigned int>& hash_distriobution)
{
    unsigned int result = 0;
    for (const auto& pair : hash_distriobution) {
        if (pair.second > 1)
            result += pair.second - 1;
    }
    return result;
}

int main(int argc, char* argv[])
{
    long int pool_size = 100'000;
    int string_len = 1000;
    if (argc > 1)
        pool_size = atol(argv[1]);

    if (argc > 2)
        string_len = atoi(argv[2]);

    std::unordered_set<std::string> string_pool;
    std::unordered_map<std::string, unsigned int> hash_function_collisions;
    std::unordered_map<unsigned int, unsigned int> hash_distribution;

    std::string collision_file_name = "./data/collisions_" + std::to_string(string_len) + ".csv";
    std::string function_file_name;

    const std::unordered_map<std::string, unsigned int (*)(const char* str, unsigned int length)>
        hash_function_array = {
            { "APHash", hash_function::APHash },
            { "BKDRHash", hash_function::BKDRHash },
            { "DEKHash", hash_function::DEKHash },
            { "DJBHash", hash_function::DJBHash },
            { "ELFHash", hash_function::ELFHash },
            { "JSHash", hash_function::JSHash },
            { "PJWHash", hash_function::PJWHash },
            { "RSHash", hash_function::RSHash },
            { "SDBMHash", hash_function::SDBMHash }
        };

    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // fill in the pool of stings
    while (string_pool.size() != pool_size) {
        string_pool.insert(string_generator::generateRandomString(string_len));
    }

    for (const auto func : hash_function_array) {
        hash_distribution.clear();

        process_hash_function(func.second, string_pool, hash_distribution);
        auto collision_number = get_collision_number(hash_distribution);

        std::cout << "hash name: " << func.first << " collision: " << collision_number << std::endl;
        
        hash_function_collisions.insert({func.first, collision_number});

        function_file_name = "./data/" + func.first + "_" + std::to_string(string_len) + "_distribution.csv";
        umap2file(hash_distribution, function_file_name.c_str());
    }
    collisions2file(hash_function_collisions, collision_file_name.c_str());
}