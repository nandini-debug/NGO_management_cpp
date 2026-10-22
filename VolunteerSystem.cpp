#include "VolunteerSystem.h"
#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <algorithm>

namespace {
std::vector<std::string> split(const std::string& line) {
    std::vector<std::string> out; std::stringstream ss(line); std::string part;
    while (std::getline(ss, part, '|')) out.push_back(part);
    return out;
}
std::string askLine(const std::string& prompt) {
    std::cout << prompt; std::string value; std::getline(std::cin, value);
    if (value.find('|') != std::string::npos) throw std::invalid_argument("The character '|' is not allowed.");
    if (value.empty()) throw std::invalid_argument("Input cannot be empty.");
    return value;
}
int askInt(const std::string& prompt) {
    std::cout << prompt; std::string s; std::getline(std::cin, s);
    std::size_t used = 0; int v;
    try { v = std::stoi(s, &used); } catch (...) { throw std::invalid_argument("Please enter a valid number."); }
    if (used != s.size() || v <= 0) throw std::invalid_argument("Enter a positive whole number.");
    return v;
}
}

VolunteerSystem::VolunteerSystem() : nextVolunteerId(1), nextEventId(1), nextAssignmentId(1) { load(); }
VolunteerSystem::~VolunteerSystem() { save(); clearVolunteers(); }
void VolunteerSystem::clearVolunteers() { for (auto* v : volunteers) delete v; volunteers.clear(); }

void VolunteerSystem::load() {
    try {
        for (const auto& line : FileManager::readLines("../Data/volunteers.txt")) {
            auto p = split(line); if (p.size() != 4) continue;
            int id = std::stoi(p[0]); volunteers.push_back(new Volunteer(id,p[1],p[2],p[3]));
            nextVolunteerId = std::max(nextVolunteerId, id+1);
        }
        for (const auto& line : FileManager::readLines("../Data/events.txt")) {
            auto p = split(line); if (p.size()!=4) continue;
            int id=std::stoi(p[0]); events.emplace_back(id,p[1],p[2],p[3]); nextEventId=std::max(nextEventId,id+1);
        }
        for (const auto& line : FileManager::readLines("../Data/assignments.txt")) {
            auto p=split(line); if(p.size()!=4) continue;
            int id=std::stoi(p[0]), v=std::stoi(p[1]), e=std::stoi(p[2]);
            assignments.emplace_back(id,v,e,p[3]); nextAssignmentId=std::max(nextAssignmentId,id+1);
        }
    } catch (const std::exception& e) { std::cerr << "Warning while loading data: " << e.what() << '\n'; }
}
void VolunteerSystem::save() const {
    std::vector<std::string> v,e,a;
    for (auto* x : volunteers) v.push_back(x->serialize());
    for (const auto& x : events) e.push_back(x.serialize());
    for (const auto& x : assignments) a.push_back(x.serialize());
    if (!FileManager::writeLines("../Data/volunteers.txt",v) ||
        !FileManager::writeLines("../Data/events.txt",e) ||
        !FileManager::writeLines("../Data/assignments.txt",a))
        std::cerr << "Could not save data. Run from the Executable folder as described in README.\n";
}
void VolunteerSystem::addVolunteer() {
    std::string n=askLine("Name: "), p=askLine("Phone: "), e=askLine("Email: ");
    volunteers.push_back(new Volunteer(nextVolunteerId++,n,p,e));
    std::cout << "Volunteer added.\n";
}
void VolunteerSystem::displayVolunteers() const {
    if(volunteers.empty()) { std::cout << "No volunteers found.\n"; return; }
    for(const auto* v:volunteers) v->display();
}
void VolunteerSystem::searchVolunteer() const {
    int id=askInt("Volunteer ID: ");
    for(const auto* v:volunteers) if(v->getId()==id) { v->display(); return; }
    std::cout << "Volunteer not found.\n";
}
void VolunteerSystem::updateVolunteer() {
    int id=askInt("Volunteer ID to update: ");
    for(auto* v:volunteers) if(v->getId()==id) {
        std::string p=askLine("New phone: "), e=askLine("New email: ");
        v->updateContact(p,e); std::cout << "Contact updated.\n"; return;
    }
    std::cout << "Volunteer not found.\n";
}
void VolunteerSystem::deleteVolunteer() {
    int id=askInt("Volunteer ID to delete: ");
    auto it=std::find_if(volunteers.begin(),volunteers.end(),[id](Volunteer* v){return v->getId()==id;});
    if(it==volunteers.end()) { std::cout << "Volunteer not found.\n"; return; }
    delete *it; volunteers.erase(it);
    assignments.erase(std::remove_if(assignments.begin(),assignments.end(),[id](const Assignment& a){return a.getVolunteerId()==id;}),assignments.end());
    std::cout << "Volunteer and related assignments deleted.\n";
}
void VolunteerSystem::addEvent() {
    std::string t=askLine("Event title: "), d=askLine("Date (e.g. 2026-11-05): "), l=askLine("Location: ");
    events.emplace_back(nextEventId++,t,d,l); std::cout << "Event added.\n";
}
void VolunteerSystem::displayEvents() const {
    if(events.empty()) { std::cout << "No events found.\n"; return; }
    for(const auto& e:events) e.display();
}
void VolunteerSystem::assignVolunteer() {
    if(volunteers.empty() || events.empty()) { std::cout << "Add at least one volunteer and one event first.\n"; return; }
    displayVolunteers(); displayEvents();
    int v=askInt("Volunteer ID: "), e=askInt("Event ID: ");
    bool vok=false, eok=false;
    for(auto* x:volunteers) if(x->getId()==v) vok=true;
    for(const auto& x:events) if(x.getId()==e) eok=true;
    if(!vok || !eok) { std::cout << "Invalid volunteer or event ID.\n"; return; }
    assignments.emplace_back(nextAssignmentId++,v,e,"Assigned");
    std::cout << "Volunteer assigned to event.\n";
}
void VolunteerSystem::report() const {
    std::cout << "\n--- NGO REPORT: " << ngo.getName() << " ---\n"
              << "Volunteers: " << volunteers.size() << "\nEvents: " << events.size()
              << "\nAssignments: " << assignments.size() << "\n";
    if(!assignments.empty()) for(const auto& a:assignments) a.display();
}
void VolunteerSystem::run() {
    bool running=true;
    while(running) {
        std::cout << "\n=== NGO VOLUNTEER MANAGEMENT ===\n"
                  << "1. Add volunteer\n2. Display volunteers\n3. Search volunteer\n"
                  << "4. Update volunteer\n5. Delete volunteer\n6. Main transaction (assign volunteer)\n"
                  << "7. Report\n8. Save/Load\n9. Manage events\n10. Exit\nChoice: ";
        std::string choice; std::getline(std::cin,choice);
        try {
            if(choice=="1") addVolunteer();
            else if(choice=="2") displayVolunteers();
            else if(choice=="3") searchVolunteer();
            else if(choice=="4") updateVolunteer();
            else if(choice=="5") deleteVolunteer();
            else if(choice=="6") assignVolunteer();
            else if(choice=="7") report();
            else if(choice=="8") { save(); std::cout << "Saved. Existing records load at startup.\n"; }
            else if(choice=="9") { std::cout << "1. Add event\n2. Display events\nChoice: "; std::getline(std::cin,choice); if(choice=="1") addEvent(); else if(choice=="2") displayEvents(); else std::cout << "Invalid choice.\n"; }
            else if(choice=="10") { save(); running=false; std::cout << "Goodbye.\n"; }
            else std::cout << "Choose a menu option from the list.\n";
        } catch(const std::exception& e) { std::cout << "Input error: " << e.what() << '\n'; }
    }
}