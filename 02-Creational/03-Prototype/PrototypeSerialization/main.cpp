#include "model/Address.h"
#include "model/Contact.h"

#include <iostream>
#include <memory>
#include <sstream>

int main()
{
    std::cout << "=== 3. Prototype via Header-Only Manual Serialization ===\n\n";

    // Step 1: Create Prototype
    auto proto_addr = std::make_unique<Address>("123 East Dr", "London", 0);
    Contact employee_proto{"Unknown Employee", std::move(proto_addr)};

    std::cout << "Prototype created successfully.\n";

    // Serialization-based Clone Function
    auto cloneViaSerialization = [](const Contact& original) -> std::unique_ptr<Contact>
    {
        std::stringstream buffer(std::ios::in | std::ios::out | std::ios::binary);

        original.serialize(buffer);
        buffer.seekg(0);

        return std::make_unique<Contact>(Contact::deserialize(buffer));
    };

    // Normal Cloning
    std::cout << "\n--- Cloning using Serialization ---\n";
    auto john = cloneViaSerialization(employee_proto);
    john->setName("John Doe");
    john->setSuite(123);

    auto jane = cloneViaSerialization(employee_proto);
    jane->setName("Jane Doe");
    jane->setSuite(125);

    std::cout << "John: " << *john << "\n";
    std::cout << "Jane: " << *jane << "\n";

    // Corner Case 1: Multiple clones
    std::cout << "\n--- Corner Case 1: Multiple clones from same prototype ---\n";
    auto bob = cloneViaSerialization(employee_proto);
    bob->setName("Bob Smith");
    bob->setSuite(300);
    std::cout << "Bob : " << *bob << "\n";

    // Corner Case 2: Creating new prototype
    std::cout << "\n--- Corner Case 2: New prototype for different office ---\n";
    auto new_addr = std::make_unique<Address>("789 North Ave", "Munich", 0);
    Contact munich_proto{"Munich Employee", std::move(new_addr)};

    auto alice = cloneViaSerialization(munich_proto);
    alice->setName("Alice Brown");
    alice->setSuite(50);

    std::cout << "Alice (Munich): " << *alice << "\n";

    // Summary
    std::cout << "\n=== Summary ===\n";
    std::cout << "- Serialization creates deep copies without Boost\n";
    std::cout << "- Works with unique_ptr safely\n";
    std::cout << "- No external compiled libraries required\n";
    std::cout << "- Original prototype remains unchanged after cloning\n";

    return 0;
}
