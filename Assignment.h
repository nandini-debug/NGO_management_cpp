#pragma once
#include <string>
class Assignment {
    int id, volunteerId, eventId;
    std::string status;
public:
    Assignment();
    Assignment(int id, int volunteerId, int eventId, const std::string& status);
    int getId() const;
    int getVolunteerId() const;
    int getEventId() const;
    std::string serialize() const;
    void display() const;
};