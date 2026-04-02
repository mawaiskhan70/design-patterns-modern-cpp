#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
    // Address fields
    std::string street_address;
    std::string post_code;
    std::string city;

    // Employment fields
    std::string company_name;
    std::string position;
    int annual_income = 0;

    // Private constructor — can't create Person directly!
    // Must use builder!
    Person() {
        std::cout << "Person created" << std::endl;
    }

public:
    ~Person() {
        std::cout << "Person destroyed" << std::endl;
    }

    // Only way to create a Person — returns builder!
    static PersonBuilder create();

    // Move constructor
    Person(Person&& other)
        : street_address(std::move(other.street_address)),
        post_code(std::move(other.post_code)),
        city(std::move(other.city)),
        company_name(std::move(other.company_name)),
        position(std::move(other.position)),
        annual_income(other.annual_income) {}

    // Move assignment
    Person& operator=(Person&& other) {
        if (this == &other) return *this;
        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    // Print person
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os
               << "Address: " << p.street_address
               << ", " << p.post_code
               << ", " << p.city
               << "\nJob: " << p.company_name
               << ", " << p.position
               << ", Income: " << p.annual_income;
    }

    // Builders need access to private fields
    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};

#endif // PERSON_H
