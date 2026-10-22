#pragma once
#include <string>
class NGO {
    std::string name;
public:
    NGO();
    explicit NGO(const std::string& name);
    std::string getName() const;
};