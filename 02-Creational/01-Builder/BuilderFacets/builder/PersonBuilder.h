#ifndef PERSON_BUILDER_H
#define PERSON_BUILDER_H

#include "PersonBuilderBase.h"

class PersonBuilder : public PersonBuilderBase {
    Person p;  // The actual Person being built!

public:
    PersonBuilder()
        : PersonBuilderBase(p) {}  // Pass our Person to base
};

#endif // PERSON_BUILDER_H
