#include "Contact.h"

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace
{
void writeString(std::ostream& os, const std::string& value)
{
    const std::uint64_t size = static_cast<std::uint64_t>(value.size());
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(value.data(), static_cast<std::streamsize>(size));
}

std::string readString(std::istream& is)
{
    std::uint64_t size = 0;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (!is)
    {
        throw std::runtime_error("Failed to read string size");
    }

    std::string value(size, '\0');
    is.read(value.data(), static_cast<std::streamsize>(size));

    if (!is)
    {
        throw std::runtime_error("Failed to read string data");
    }

    return value;
}
}

Contact::Contact(const std::string& name, std::unique_ptr<Address> addr)
    : name{name}, address{std::move(addr)}
{
}

Contact::Contact(const Contact& other)
    : name{other.name},
    address{other.address ? std::make_unique<Address>(*other.address) : nullptr}
{
}

std::string Contact::getName() const
{
    return name;
}

void Contact::setName(const std::string& newName)
{
    name = newName;
}

Address* Contact::getAddress() const
{
    return address.get();
}

void Contact::setSuite(int suite)
{
    if (address)
    {
        address->setSuite(suite);
    }
}

std::ostream& operator<<(std::ostream& os, const Contact& obj)
{
    os << "name: " << obj.name;

    if (obj.address)
    {
        os << " works at " << *obj.address;
    }
    else
    {
        os << " has no address";
    }

    return os;
}

void Contact::serialize(std::ostream& os) const
{
    writeString(os, name);

    const bool hasAddress = (address != nullptr);
    os.write(reinterpret_cast<const char*>(&hasAddress), sizeof(hasAddress));

    if (hasAddress)
    {
        address->serialize(os);
    }

    if (!os)
    {
        throw std::runtime_error("Failed to serialize Contact");
    }
}

Contact Contact::deserialize(std::istream& is)
{
    Contact contact;
    contact.name = readString(is);

    bool hasAddress = false;
    is.read(reinterpret_cast<char*>(&hasAddress), sizeof(hasAddress));

    if (!is)
    {
        throw std::runtime_error("Failed to read Contact address flag");
    }

    if (hasAddress)
    {
        contact.address = std::make_unique<Address>(Address::deserialize(is));
    }

    return contact;
}
