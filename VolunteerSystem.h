#pragma once
#include "Volunteer.h"
#include "Event.h"
#include "Skill.h"
#include "Assignment.h"
#include "NGO.h"
#include <vector>
#include <string>

class VolunteerSystem {
    std::vector<Volunteer*> volunteers; // polymorphic base pointers
    std::vector<Event> events;
    std::vector<Skill> skills;
    std::vector<Assignment> assignments;
    NGO ngo;
    int nextVolunteerId, nextEventId, nextAssignmentId;
    void addVolunteer();
    void displayVolunteers() const;
    void searchVolunteer() const;
    void updateVolunteer();
    void deleteVolunteer();
    void addEvent();
    void displayEvents() const;
    void assignVolunteer();
    void report() const;
    void load();
    void save() const;
    void clearVolunteers();
public:
    VolunteerSystem();
    ~VolunteerSystem();
    void run();
};