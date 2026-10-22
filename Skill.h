#pragma once
#include <string>
class Skill {
    int id;
    std::string name;
public:
    Skill();
    Skill(int id, const std::string& name);
    int getId() const;
    std::string getName() const;
};