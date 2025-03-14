#include "GenePool.h"

// GenePool Member Functions

GenePool::GenePool(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') {
            // Skip empty lines and comment lines
            continue;
        }
        std::istringstream iss(line);
        std::string name, genderStr, motherName, fatherName;

        // Assuming the format is: Name, Gender, Mother, Father
        std::getline(iss, name, '\t');
        std::getline(iss, genderStr, '\t');
        std::getline(iss, motherName, '\t');
        std::getline(iss, fatherName, '\t');

        Gender gender = (genderStr == "female") ? Gender::FEMALE : Gender::MALE;

        Person* person = new Person(name, gender);
        addPerson(person);

        if (!motherName.empty()) {
            Person* mother = find(motherName);
            if (mother) {
                person->addParent(Gender::FEMALE, mother);
                person->mother()->addChild(person);
            }
        }

        if (!fatherName.empty()) {
            Person* father = find(fatherName);
            if (father) {
                person->addParent(Gender::MALE, father);
                person->father()->addChild(person);
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

