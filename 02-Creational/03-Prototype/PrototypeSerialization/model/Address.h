#pragma once

#include <cstdint>
#include <iostream>
#include <string>

class Address
{
private:
    std::string street;
    std::string city;
    int suite {};

public:
    Address() = default;

    Address(const std::string& street, const std::string& city, int suite);
    Address(const Address& other);

    std::string getStreet() const;
    std::string getCity() const;
    int getSuite() const;
    void setSuite(int suite);

    friend std::ostream& operator<<(std::ostream& os, const Address& obj);

    // Header-only manual serialization
    void serialize(std::ostream& os) const;
    static Address deserialize(std::istream& is);
};
