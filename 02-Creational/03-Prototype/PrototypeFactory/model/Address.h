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
    Address(const Address& other);

    std::string getStreet() const;
    std::string getCity() const;
    int getSuite() const;
    void setSuite(int suite);

    friend std::ostream& operator<<(std::ostream& os, const Address& obj);
};
