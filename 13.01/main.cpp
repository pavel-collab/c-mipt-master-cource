#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <iostream>

std::string bytes_to_hex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    
    for (uint8_t byte : data) {
        oss << std::setw(2) << static_cast<int>(byte);
    }
    
    return oss.str();
}

int main()
{
    std::vector<uint8_t> data = {0xBA, 0xAD, 0x0F, 0xE1};
    std::cout << bytes_to_hex(data); // Выведет "BAAD0FE1"
}