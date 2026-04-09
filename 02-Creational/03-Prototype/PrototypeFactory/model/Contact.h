#pragma once
#include "Address.h"
#include <memory>
#include <string>
#include <iostream>

class Contact
{
private:
    std::string name;
    std::unique_ptr<Address> address;

public:
    Contact(const std::string& name, std::unique_ptr<Address> addr);
    Contact(const Contact& other);           // Prototype copy constructor
    Contact& operator=(const Contact& other);

    std::string getName() const;
    void setName(const std::string& name);

    Address* getAddress() const;   // non-owning access
    void setSuite(int suite);

    ~Contact() = default;

    friend std::ostream& operator<<(std::ostream& os, const Contact& obj);
};
