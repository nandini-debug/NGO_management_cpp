#include "Assignment.h"
#include <iostream>
#include <sstream>
Assignment::Assignment() : id(0), volunteerId(0), eventId(0), status("Assigned") {}
Assignment::Assignment(int i, int v, int e, const std::string& s) : id(i), volunteerId(v), eventId(e), status(s) {}
int Assignment::getId() const { return id; }
int Assignment::getVolunteerId() const { return volunteerId; }
int Assignment::getEventId() const { return eventId; }
std::string Assignment::serialize() const { std::ostringstream o; o << id << '|' << volunteerId << '|' << eventId << '|' << status; return o.str(); }
void Assignment::display() const { std::cout << "Assignment ID: " << id << " | Volunteer: " << volunteerId << " | Event: " << eventId << " | Status: " << status << '\n'; }