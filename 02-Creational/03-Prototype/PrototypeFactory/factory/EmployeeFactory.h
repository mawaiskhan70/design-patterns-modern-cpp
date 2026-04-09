#pragma once
#include "../model/Contact.h"
#include <memory>
#include <string>

class EmployeeFactory
{
private:
    // Static prototypes (shared templates)
    static Contact main_office;
    static Contact aux_office;

    // Private helper that does the actual cloning
    static std::unique_ptr<Contact> NewEmployee(const std::string& name, int suite, const Contact& prototype);

public:
    static std::unique_ptr<Contact> NewMainOfficeEmployee(const std::string& name, int suite);
    static std::unique_ptr<Contact> NewAuxOfficeEmployee(const std::string& name, int suite);
};
