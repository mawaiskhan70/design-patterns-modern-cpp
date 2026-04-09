#include "Address.h"

#include <stdexcept>

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

Address::Address(const std::string& street, const std::string& city, int suite)
    : street{street}, city{city}, suite{suite}
{
}

Address::Address(const Address& other)
    : street{other.street}, city{other.city}, suite{other.suite}
{
}

std::string Address::getStreet() const
{
    return street;
}

std::string Address::getCity() const
{
    return city;
}

int Address::getSuite() const
{
    return suite;
}

void Address::setSuite(int newSuite)
{
    suite = newSuite;
}

std::ostream& operator<<(std::ostream& os, const Address& obj)
{
    return os << "street: " << obj.street
              << " city: " << obj.city
              << " suite: " << obj.suite;
}

void Address::serialize(std::ostream& os) const
{
    writeString(os, street);
    writeString(os, city);
    os.write(reinterpret_cast<const char*>(&suite), sizeof(suite));

    if (!os)
    {
        throw std::runtime_error("Failed to serialize Address");
    }
}

Address Address::deserialize(std::istream& is)
{
    Address addr;
    addr.street = readString(is);
    addr.city = readString(is);
    is.read(reinterpret_cast<char*>(&addr.suite), sizeof(addr.suite));

    if (!is)
    {
        throw std::runtime_error("Failed to deserialize Address");
    }

    return addr;
}
