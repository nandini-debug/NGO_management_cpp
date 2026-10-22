#include "Volunteer.h"
#include <sstream>
Volunteer::Volunteer() : id(0), name(""), phone(""), email("") {}
Volunteer::Volunteer(int i, const std::string& n, const std::string& p, const std::string& e)
    : id(i), name(n), phone(p), email(e) {}
Volunteer::~Volunteer() = default;
int Volunteer::getId() const { return id; }
std::string Volunteer::getName() const { return name; }
std::string Volunteer::role() const { return "Volunteer"; }
void Volunteer::display() const {
    std::cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone
              << " | Email: " << email << " | Role: " << role() << '\n';
}
void Volunteer::updateContact(const std::string& p, const std::string& e) { phone = p; email = e; }
std::string Volunteer::serialize() const {
    std::ostringstream out; out << id << '|' << name << '|' << phone << '|' << email; return out.str();
}