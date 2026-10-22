#pragma once
#include <string>
#include <iostream>

class Volunteer {
protected:
    int id;
    std::string name, phone, email;
public:
    Volunteer();
    Volunteer(int id, const std::string& name, const std::string& phone, const std::string& email);
    virtual ~Volunteer();
    int getId() const;
    std::string getName() const;
    virtual std::string role() const;
    virtual void display() const;
    void updateContact(const std::string& phone, const std::string& email);
    virtual std::string serialize() const;
};