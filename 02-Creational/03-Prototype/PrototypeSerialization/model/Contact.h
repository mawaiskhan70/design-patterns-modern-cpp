#pragma once

#include "Address.h"

#include <iostream>
#include <memory>
#include <string>

class Contact
{
private:
    std::string name;
    std::unique_ptr<Address> address;

public:
    Contact() = default;

    Contact(const std::string& name, std::unique_ptr<Address> addr);
    Contact(const Contact& other);

    std::string getName() const;
    void setName(const std::string& name);

    Address* getAddress() const;
    void setSuite(int suite);

    ~Contact() = default;

    friend std::ostream& operator<<(std::ostream& os, const Contact& obj);

    // Header-only manual serialization
    void serialize(std::ostream& os) const;
    static Contact deserialize(std::istream& is);
};
