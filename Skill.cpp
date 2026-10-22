#include "Skill.h"
Skill::Skill() : id(0), name("") {}
Skill::Skill(int i, const std::string& n) : id(i), name(n) {}
int Skill::getId() const { return id; }
std::string Skill::getName() const { return name; }