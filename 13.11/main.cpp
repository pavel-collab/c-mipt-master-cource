#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <openssl/sha.h>

namespace fs = std::filesystem;

struct FileInfo {
    fs::path path;
    uintmax_t size;
    std::string hash;
};

std::string sha1_hash(const fs::path& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) throw std::runtime_error("Can't open file: " + file_path.string());

    SHA_CTX ctx;
    SHA1_Init(&ctx);

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
        SHA1_Update(&ctx, buffer, file.gcount());
    }

    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1_Final(digest, &ctx);

    std::ostringstream oss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return oss.str();
}

std::vector<FileInfo> collect_files(const fs::path& root) {
    std::vector<FileInfo> files;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        try {
            if (entry.is_regular_file() && !entry.is_symlink()) {
                files.push_back({
                    entry.path(),
                    entry.file_size(),
                    sha1_hash(entry.path())
                });
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << " | " << entry.path() << "\n";
        }
    }
    return files;
}

void deduplicate(const std::vector<FileInfo>& files) {
    std::unordered_map<std::string, std::vector<fs::path>> groups;
    for (const auto& fi : files) {
        groups[fi.hash + std::to_string(fi.size)].push_back(fi.path);
    }

    for (const auto& [key, paths] : groups) {
        if (paths.size() < 2) continue;

        const auto original = fs::absolute(paths.front());
        for (auto it = paths.begin()+1; it != paths.end(); ++it) {
            try {
                fs::remove(*it);
                fs::create_symlink(original, *it);
                std::cout << "Created symlink: " << *it << " -> " << original << "\n";
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Failed: " << e.path1() << " | " << e.what() << "\n";
            }
        }
    }
}

// g++ -std=c++17 -O2 -lcrypto main.cpp
//! ATTENTION: here we're using depricated in OpenSSL functions for hashing
int main() {
    std::string path;
    std::cout << "Directory to scan: ";
    std::cin >> path;

    try {
        deduplicate(collect_files(path));
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}