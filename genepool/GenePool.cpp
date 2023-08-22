#include "GenePool.h"

// GenePool Member Functions
GenePool::GenePool(std::istream& stream) {
    std::string line;
    while(std::getline(stream, line)) {
        if(!line.empty() && line[0] != '#') {
            std::string name, genderStr, motherName, fatherName;
            Gender gender;

            std::istringstream lineStream(line);
            lineStream >> name >> genderStr >> motherName >> fatherName;

            if(genderStr == "male") {
                gender = Gender::MALE;
            }
            else if (genderStr == "female") {
                gender = Gender::FEMALE;
            }
            else {
                throw std::invalid_argument("Invalid gender: " + genderStr);
            }

            Person* person = new Person(name, gender);
            addPerson(person);
        }
    }
}

GenePool::~GenePool() {
    for (auto& pair: people) {
        delete pair.second;
    }
}

void GenePool::addPerson(Person* person) {
    people[person->name()] = person;
}

std::set<Person*> GenePool::everyone() const {
    std::set<Person*> result; 
    for(const auto& pair : people) {
        result.insert(pair.second);
    }
    return result;
}

Person* GenePool::find(const std::string& name) const {
    auto it = people.find(name);
    if(it != people.end()) {
        return it->second;
    }
    return nullptr;
}