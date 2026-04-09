#include "factory/EmployeeFactory.h"
#include "model/Address.h"
#include "model/Contact.h"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "=== 2. Prototype Factory Pattern (Modern OOP with Classes + unique_ptr) ===\n\n";

    // =============================================================
    // Normal Usage of Prototype Factory
    // =============================================================
    std::cout << "--- Normal Usage ---\n";
    auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);

    std::cout << "John: " << *john << "\n";
    std::cout << "Jane: " << *jane << "\n";

    // =============================================================
    // Corner Case 1: Creating another employee from same prototype
    // =============================================================
    std::cout << "\n--- Corner Case 1: More employees from same prototype ---\n";
    auto bob = EmployeeFactory::NewMainOfficeEmployee("Bob Smith", 200);
    std::cout << "Bob : " << *bob << "\n";

    // =============================================================
    // Corner Case 2: What if we want a completely new office prototype?
    // =============================================================
    std::cout << "\n--- Corner Case 2: Need a new office prototype? ---\n";
    std::cout << "Solution: We can extend EmployeeFactory later or create new static prototypes.\n";
    // For now, we show creating directly (in real code we would add to factory)
    auto new_proto_addr = std::make_unique<Address>("789 North Ave", "Munich", 0);
    Contact munich_proto{"Munich Employee", std::move(new_proto_addr)};

    Contact munich_employee{munich_proto};
    munich_employee.setName("Alice Brown");
    munich_employee.setSuite(50);

    std::cout << "Munich Employee: " << munich_employee << "\n";

    // =============================================================
    // Corner Case 3: Moved-from state awareness
    // =============================================================
    std::cout << "\n--- Corner Case 3: Moved-from unique_ptr behavior ---\n";
    auto temp_addr = std::make_unique<Address>("Temp", "City", 999);
    Contact temp_contact{"Temp", std::move(temp_addr)};

    if (!temp_addr) {
        std::cout << "temp_addr is now null after move (moved-from state).\n";
        std::cout << "   → Cannot reuse it. Must create new make_unique if needed.\n";
    }

    std::cout << "\n=== Summary ===\n";
    std::cout << "• Prototype Factory holds static prototype objects (main_office, aux_office)\n";
    std::cout << "• It clones them using copy constructor and customizes only needed fields\n";
    std::cout << "• unique_ptr ensures safe memory management and exclusive ownership\n";
    std::cout << "• Deep copies are created automatically — no shared data bugs\n";

    return 0;
}
