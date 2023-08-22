#include "GenePool.h"

// GenePool Member Functions
GenePool::GenePool(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string name, genderStr, motherName, fatherName;

        // Assuming the format is: Name, Gender, Mother, Father
        std::getline(iss, name, '\t');
        std::getline(iss, genderStr, '\t');
        std::getline(iss, motherName, '\t');
        std::getline(iss, fatherName, '\t');

        Gender gender;

        if(genderStr == "FEMALE") {
            gender = Gender::FEMALE;
        }
        else {
            gender = Gender::MALE;
        }

        Person* person = new Person(name, gender);
        addPerson(person);

        if (!motherName.empty()) {
            Person* mother = find(motherName);
            if (mother) {
                person->addParent(Gender::FEMALE, mother);
            }
        }

        if (!fatherName.empty()) {
            Person* father = find(fatherName);
            if (father) {
                person->addParent(Gender::MALE, father);
            }
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

