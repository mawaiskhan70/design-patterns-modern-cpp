#include "Contact.h"

Contact::Contact(const std::string& name, std::unique_ptr<Address> addr)
    : name{name}, address{std::move(addr)} {}

Contact::Contact(const Contact& other)
    : name{other.name},
    address{std::make_unique<Address>(*other.address)}   // Deep copy
{}

Contact& Contact::operator=(const Contact& other)
{
    if (this == &other) return *this;
    name = other.name;
    address = std::make_unique<Address>(*other.address);
    return *this;
}

std::string Contact::getName() const { return name; }
void Contact::setName(const std::string& newName) { name = newName; }

Address* Contact::getAddress() const { return address.get(); }
void Contact::setSuite(int suite) { if (address) address->setSuite(suite); }

std::ostream& operator<<(std::ostream& os, const Contact& obj)
{
    return os << "name: " << obj.name << " works at " << *obj.address;
}
