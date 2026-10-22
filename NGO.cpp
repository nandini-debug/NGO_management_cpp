#include "NGO.h"
NGO::NGO() : name("Community NGO") {}
NGO::NGO(const std::string& n) : name(n) {}
std::string NGO::getName() const { return name; }