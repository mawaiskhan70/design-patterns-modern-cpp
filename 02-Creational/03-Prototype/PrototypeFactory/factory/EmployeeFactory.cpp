#include "EmployeeFactory.h"
#include "../model/Address.h"

Contact EmployeeFactory::main_office{"", std::make_unique<Address>("123 East Dr", "London", 0)};
Contact EmployeeFactory::aux_office{"", std::make_unique<Address>("123B East Dr", "London", 0)};

std::unique_ptr<Contact> EmployeeFactory::NewEmployee(const std::string& name, int suite, const Contact& prototype)
{
    auto result = std::make_unique<Contact>(prototype);   // Prototype clone (deep copy)
    result->setName(name);
    result->setSuite(suite);
    return result;
}

std::unique_ptr<Contact> EmployeeFactory::NewMainOfficeEmployee(const std::string& name, int suite)
{
    return NewEmployee(name, suite, main_office);
}

std::unique_ptr<Contact> EmployeeFactory::NewAuxOfficeEmployee(const std::string& name, int suite)
{
    return NewEmployee(name, suite, aux_office);
}
