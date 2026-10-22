#pragma once
#include <string>
#include <vector>
class FileManager {
public:
    static std::vector<std::string> readLines(const std::string& path);
    static bool writeLines(const std::string& path, const std::vector<std::string>& lines);
};