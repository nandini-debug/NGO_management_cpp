#pragma once
#include <string>
class Event {
    int id;
    std::string title, date, location;
public:
    Event();
    Event(int id, const std::string& title, const std::string& date, const std::string& location);
    int getId() const;
    std::string getTitle() const;
    std::string serialize() const;
    void display() const;
};