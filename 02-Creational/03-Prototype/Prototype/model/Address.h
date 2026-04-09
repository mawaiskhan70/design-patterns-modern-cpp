#pragma once
#include <string>
#include <iostream>

class Address
{
private:
    std::string street;
    std::string city;
    int suite;

public:
    Address(const std::string& street, const std::string& city, int suite);

    // Copy constructor (needed for deep copy in Contact)
    Address(const Address& other);

    // Getters (we will use them in Contact and main)
    std::string getStreet() const;
    std::string getCity() const;
    int getSuite() const;

    // Setter for suite (used when customizing cloned employee)
    void setSuite(int suite);

    friend std::ostream& operator<<(std::ostream& os, const Address& obj);
};
