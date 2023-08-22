#ifndef PERSON_H
#define PERSON_H

#include "Enums.h"

#include <set>
#include <string>

// This is the Person class you need to implement.
// It has many member functions that perform relationship queries.
// Add any member variables you need to support this.
// Implement the member functions in Person.cpp.

class Person {
  // Member Variables
private:
  std::string mName;
  Gender mGender;
  Person* mMother;
  Person* mFather;
  std::set<Person*> mChildren;
  // Helper Functions

public:
  // Constructor
  Person(const std::string& name, Gender gender);
  // Destructor?

  // Required Getter Functions
  const std::string& name()   const;
  Gender             gender() const;
  Person*            mother();
  Person*            father();

  // Required Relationship Functions
  std::set<Person*> ancestors(PMod pmod = PMod::ANY); // DONE
  std::set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // DONE
  std::set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // DONE
  std::set<Person*> children(); // DONE
  std::set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // stub
  std::set<Person*> daughters(); // stub
  std::set<Person*> descendants(); // stub
  std::set<Person*> grandchildren(); // stub
  std::set<Person*> granddaughters(); // stub
  std::set<Person*> grandfathers(PMod pmod = PMod::ANY); // DONE
  std::set<Person*> grandmothers(PMod pmod = PMod::ANY); // DONE
  std::set<Person*> grandparents(PMod pmod = PMod::ANY); // DONE
  std::set<Person*> grandsons(); // stub
  std::set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // stub
  std::set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // stub
  std::set<Person*> parents(PMod pmod = PMod::ANY); // DONE
  std::set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // DONE
  std::set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // DONE
  std::set<Person*> sons(); // stub
  std::set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY); // DONE

  // Other Member Functions
  void addParent(Gender parentGender, Person* parent);
  void addChild(Person* child);
};
#endif
