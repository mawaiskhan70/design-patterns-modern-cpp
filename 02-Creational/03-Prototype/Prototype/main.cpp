#include "model/Address.h"
#include "model/Contact.h"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "=== 1. Prototype Pattern (Modern OOP with Classes + unique_ptr) ===\n\n";

    // =============================================================
    // Step 1: Create Prototype Address
    // =============================================================
    auto proto_addr = std::make_unique<Address>("123 East Dr", "London", 0);
    std::cout << "1. proto_addr created and owns the Address.\n";

    // =============================================================
    // Step 2: Create Prototype Employee (transfer ownership using move)
    // =============================================================
    Contact employee_proto{"Unknown Employee", std::move(proto_addr)};
    std::cout << "2. employee_proto now owns the Address (proto_addr is now null).\n";

    // =============================================================
    // Corner Case 1: Trying to use proto_addr after move (Demonstrates danger)
    // =============================================================
    std::cout << "\n--- Corner Case 1: Using moved-from unique_ptr ---\n";
    if (proto_addr) {
        std::cout << "proto_addr is still valid.\n";
    } else {
        std::cout << "proto_addr is now NULL/empty after std::move.\n";
        std::cout << "   → You cannot use it anymore. It is in 'moved-from' state.\n";
    }

    // =============================================================
    // Corner Case 2: What if we need another prototype later?
    // =============================================================
    std::cout << "\n--- Corner Case 2: Need a new prototype later? ---\n";
    std::cout << "Solution: Create a fresh new Address using make_unique again.\n";

    auto new_proto_addr = std::make_unique<Address>("456 West Rd", "Berlin", 0);
    Contact another_employee_proto{"Another Unknown", std::move(new_proto_addr)};

    std::cout << "   → New prototype created successfully for Berlin office.\n";

    // =============================================================
    // Normal Prototype Usage (Cloning)
    // =============================================================
    std::cout << "\n=== Normal Prototype Cloning ===\n";

    Contact john{employee_proto};     // Deep copy using Prototype
    john.setName("John Doe");
    john.setSuite(123);

    Contact jane{employee_proto};     // Another deep copy
    jane.setName("Jane Doe");
    jane.setSuite(125);

    std::cout << "John: " << john << "\n";
    std::cout << "Jane: " << jane << "\n";

    // =============================================================
    // Corner Case 3: Cloning after move (still works because we clone Contact)
    // =============================================================
    std::cout << "\n--- Corner Case 3: Cloning works even after original move ---\n";
    Contact bob{employee_proto};
    bob.setName("Bob Smith");
    bob.setSuite(200);

    std::cout << "Bob : " << bob << "\n";

    std::cout << "\n=== Summary ===\n";
    std::cout << "• After std::move, the source unique_ptr becomes null.\n";
    std::cout << "• Always create a new make_unique<Address>() if you need another prototype.\n";
    std::cout << "• Cloning Contact (using copy constructor) creates independent deep copies.\n";
    std::cout << "• No memory leaks - unique_ptr handles cleanup automatically.\n";

    return 0;
}
