#pragma once
#include "Address.h"
#include <memory>
#include <string>
#include <iostream>

class Contact
{
private:
    std::string name;
    std::unique_ptr<Address> address;   // Modern smart pointer - no raw pointer!

public:
    // Constructor
    Contact(const std::string& name, std::unique_ptr<Address> addr);

    // Prototype Pattern: Copy constructor (deep copy)
    Contact(const Contact& other);

    // Copy assignment (Rule of Five friendly)
    Contact& operator=(const Contact& other);

    // Getters / Setters for demo
    std::string getName() const;
    void setName(const std::string& name);

    Address* getAddress() const;           // returns raw pointer for convenience (non-owning)
    void setSuite(int suite);              // convenience method

    ~Contact() = default;   // unique_ptr cleans up automatically

    friend std::ostream& operator<<(std::ostream& os, const Contact& obj);
};
