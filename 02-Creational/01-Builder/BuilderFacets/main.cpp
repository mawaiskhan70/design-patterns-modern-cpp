#include <iostream>
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

using namespace std;

int main() {

    // ═══════════════════════════════════════
    // Use Case 1: Full Person (Address + Job)
    // ═══════════════════════════════════════
    cout << "=== Full Person ===" << endl;

    Person p = Person::create()
                   .lives()
                   .at("123 London Road")
                   .with_postcode("SW1 1GB")
                   .in("London")
                   .works()
                   .at("PragmaSoft")
                   .as_a("Consultant")
                   .earning(10000000);

    cout << p << endl;

    // ═══════════════════════════════════════
    // Use Case 2: Only Address
    // ═══════════════════════════════════════
    cout << "\n=== Only Address ===" << endl;

    Person p2 = Person::create()
                    .lives()
                    .at("456 Baker Street")
                    .with_postcode("NW1 6XE")
                    .in("London");

    cout << p2 << endl;

    // ═══════════════════════════════════════
    // Use Case 3: Only Job
    // ═══════════════════════════════════════
    cout << "\n=== Only Job ===" << endl;

    Person p3 = Person::create()
                    .works()
                    .at("Google")
                    .as_a("Software Engineer")
                    .earning(150000);

    cout << p3 << endl;

    // ═══════════════════════════════════════
    // Use Case 4: Multiple Persons
    // ═══════════════════════════════════════
    cout << "\n=== Team ===" << endl;

    Person developer = Person::create()
                           .lives()
                           .at("789 Tech Avenue")
                           .with_postcode("CA 94025")
                           .in("San Francisco")
                           .works()
                           .at("Meta")
                           .as_a("Senior Developer")
                           .earning(200000);

    Person designer = Person::create()
                          .lives()
                          .at("321 Art Street")
                          .with_postcode("NY 10001")
                          .in("New York")
                          .works()
                          .at("Meta")
                          .as_a("UX Designer")
                          .earning(180000);

    cout << "Developer:\n" << developer << endl;
    cout << "\nDesigner:\n" << designer << endl;

    return 0;
}
