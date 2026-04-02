#ifndef PERSON_BUILDER_BASE_H
#define PERSON_BUILDER_BASE_H

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase{

protected:
    Person& person;
    explicit PersonBuilderBase(Person &person) : person(person) {}

public:
    // Convert builder to Person (when building is done)
    operator Person() const {
        return std::move(person);
    }

    // Switch to address builder
    PersonAddressBuilder lives() const;

    // Switch to job builder
    PersonJobBuilder works() const;
};

#endif // PERSON_BUILDER_BASE_H
