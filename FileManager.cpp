#include "FileManager.h"
#include <fstream>
std::vector<std::string> FileManager::readLines(const std::string& path) {
    std::vector<std::string> lines; std::ifstream in(path); std::string line;
    while (std::getline(in, line)) if (!line.empty()) lines.push_back(line);
    return lines;
}
bool FileManager::writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream out(path); if (!out) return false;
    for (const auto& line : lines) out << line << '\n';
    return static_cast<bool>(out);
}