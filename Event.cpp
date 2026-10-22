#include "Event.h"
#include <iostream>
#include <sstream>
Event::Event() : id(0), title(""), date(""), location("") {}
Event::Event(int i, const std::string& t, const std::string& d, const std::string& l)
    : id(i), title(t), date(d), location(l) {}
int Event::getId() const { return id; }
std::string Event::getTitle() const { return title; }
std::string Event::serialize() const { std::ostringstream o; o << id << '|' << title << '|' << date << '|' << location; return o.str(); }
void Event::display() const { std::cout << "Event ID: " << id << " | " << title << " | " << date << " | " << location << '\n'; }