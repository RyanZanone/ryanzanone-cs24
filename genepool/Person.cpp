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

std::set<Person*> Person::children() {
    return mChildren;
}

void Person::addParent(Gender parentGender, Person* parent) {
    if(parentGender == Gender::FEMALE) {
        mMother = parent;
    }
    else if (parentGender == Gender::MALE) {
        mFather = parent;
    }
}

void Person::addChild(Person* child) {
    mChildren.insert(child);
}

std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> result;

    if((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mMother) {
        result.insert(mMother);
    }
    else if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && mFather) {
        result.insert(mFather);
    }
    
    return result;
}

std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother != nullptr) {
            result.insert(mMother);
            std::set<Person*> maternalAncestors = mMother->ancestors(PMod::ANY);
            result.insert(maternalAncestors.begin(), maternalAncestors.end());
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather != nullptr) {
            result.insert(mFather);
            std::set<Person*> paternalAncestors = mFather->ancestors(PMod::ANY);
            result.insert(paternalAncestors.begin(), paternalAncestors.end());
        }
    }

    return result;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (mMother) {
        std::set<Person*> maternalAunts = mMother->sisters(pmod, smod);
        for(Person* aunt : maternalAunts) {
            result.insert(aunt);
        }
    }

    if (mFather) {
        std::set<Person*> paternalAunts = mFather->sisters(pmod, smod);
        for(Person* aunt : paternalAunts) {
            result.insert(aunt);
        }
    }

    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if(mMother) {
        std::set<Person*> maternalUncles = mMother->brothers(pmod, smod);
        for(Person* uncle : maternalUncles) {
            result.insert(uncle);
        }
    }

    if(mFather) {
        std::set<Person*> paternalUncles = mFather->brothers(pmod, smod); 
        for(Person* uncle : paternalUncles) {
            result.insert(uncle);
        }
    }

    return result;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if(smod == SMod::FULL) {
        if(mMother && mFather) {
            std::set<Person*> allSibs;
            std::set<Person*> maternalSibs = mMother->children();
            std::set<Person*> paternalSibs = mFather->children();
            if(pmod == PMod::MATERNAL) {
                for(Person* sib : maternalSibs) {
                    if(sib->mother() == mMother && sib->father() == mFather) {
                        result.insert(sib);
                    }
                }
                return result;
            }
            else if (pmod == PMod::PATERNAL) {
                for(Person* sib : paternalSibs) {
                    if(sib->mother() == mMother && sib->father() == mFather) {
                        result.insert(sib);
                    }
                }
                return result;
            }
            else {
                for(Person* sib : maternalSibs) {
                    if(sib->mother() == mMother && sib->father() == mFather) {
                        result.insert(sib);
                    }
                }
                for(Person* sib : paternalSibs) {
                    if(sib->mother() == mMother && sib->father() == mFather) {
                        result.insert(sib);
                    }
                }
                return result;
            }
        }
    }
    
    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> result;
    std::set<Person*> allSibs = siblings(pmod, smod);

    for(Person* sib : allSibs) {
        if(sib->gender() == Gender::MALE) {
            result.insert(sib);
        }
    }

    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> result;
    std::set<Person*> allSibs = siblings(pmod, smod);

    for(Person* sib : allSibs) {
        if(sib->gender() == Gender::FEMALE) {
            result.insert(sib);
        }
    }

    return result;
}

std::set<Person*> Person::daughters() {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::sons() {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;

    return result; 
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> result;

    return result; 
}

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> result;

    return result;
}

std::set<Person*> Person::descendants() {
    std::set<Person*> result;

    return result;
}