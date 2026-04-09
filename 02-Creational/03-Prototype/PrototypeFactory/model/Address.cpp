#include "Address.h"

Address::Address(const std::string& street, const std::string& city, int suite)
    : street{street}, city{city}, suite{suite} {}

Address::Address(const Address& other)
    : street{other.street}, city{other.city}, suite{other.suite} {}

std::string Address::getStreet() const { return street; }
std::string Address::getCity() const { return city; }
int Address::getSuite() const { return suite; }
void Address::setSuite(int newSuite) { suite = newSuite; }

std::ostream& operator<<(std::ostream& os, const Address& obj)
{
    return os << "street: " << obj.street
              << " city: " << obj.city
              << " suite: " << obj.suite;
}
