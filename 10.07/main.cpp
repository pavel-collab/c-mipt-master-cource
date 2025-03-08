#include "hash_functions.hpp"
#include "string_generator.hpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <array>

void process_hash_function(unsigned int (*hash_function) (const char* str, unsigned int length),
                           std::unordered_set<std::string>& string_pool,
                           std::unordered_map<unsigned int, unsigned int>& hash_distriobution)
{
    for (auto str : string_pool)
    {
        auto hash = hash_function(str.c_str(), str.length());
        hash_distriobution[hash]++;
    }
}

unsigned int get_collision_number(std::unordered_map<unsigned int, unsigned int>& hash_distriobution)
{
    unsigned int result = 0;
    for (const auto& pair : hash_distriobution)
    {
        if (pair.second > 1)
            result++;
    }
    return result;
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    long unsigned int pool_size = 10'000'000;
    int string_random_length;
    int length_offset = 15;
    int length_range = 60;
    unsigned int (*hash_function_array[9])(const char* str, 
                                     unsigned int length) = {
                                        hash_function::APHash,
                                        hash_function::BKDRHash,
                                        hash_function::DEKHash,
                                        hash_function::DJBHash,
                                        hash_function::ELFHash,
                                        hash_function::JSHash,
                                        hash_function::PJWHash,
                                        hash_function::RSHash,
                                        hash_function::SDBMHash
                                     };
    
    std::unordered_set<std::string> string_pool;

    // fill in the pool of stings
    while (string_pool.size() != pool_size)
    {
        string_random_length = length_offset + (rand() % length_range);
        string_pool.insert(string_generator::generateRandomString(string_random_length));
    }

    for (const auto func : hash_function_array)
    {
        std::unordered_map<unsigned int, unsigned int> hash_distribution;
        process_hash_function(func, string_pool, hash_distribution);
        auto collision_number = get_collision_number(hash_distribution);
        std::cout << collision_number << std::endl;
    }
}