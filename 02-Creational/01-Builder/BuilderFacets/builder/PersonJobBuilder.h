#ifndef PERSON_JOB_BUILDER_H
#define PERSON_JOB_BUILDER_H

#include <string>
#include "PersonBuilderBase.h"

class PersonJobBuilder : public PersonBuilderBase {
    using Self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilderBase(person) {}

    Self& at(std::string company_name) {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(std::string position) {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

#endif // PERSON_JOB_BUILDER_H
