#include "Person.h"

// Person Member Functions

Person::Person(const std::string& name, Gender gender) {
    mName = name;
    mGender = gender;
    mMother = nullptr;
    mFather = nullptr;
}

const std::string& Person::name() const {
    return mName;
}

Gender Person::gender() const {
    return mGender;
}

Person* Person::mother() {
    return mMother;
}

Person* Person::father() {
    return mFather;
}

void addParent(Gender parentGender, Person* parent) {
    if(parentGender == Gender::FEMALE) {
        mMother = parent;
    }
    else if (parentGender == Gender::MALE) {
        mFather = parent;
    }
}