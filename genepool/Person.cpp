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

    if(pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if(mMother) {
            result.insert(mMother);
        }
    }

    if(pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if(mFather) {
            result.insert(mFather);
        }
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
    std::set<Person*> maternalSiblings;
    std::set<Person*> paternalSiblings;

    if(pmod == PMod::ANY && smod == SMod::ANY) {
        if(mMother && mFather) {
            maternalSiblings = mMother->children();
            paternalSiblings = mFather->children();
        }
        result = maternalSiblings | paternalSiblings;
    }
    else if(smod == SMod::FULL) {
        if(mMother && mFather) {
            maternalSiblings = mMother->children();
            paternalSiblings = mFather->children();
            for(Person* sib : maternalSiblings) {
                if(sib->father() == mFather) {
                    result.insert(sib);
                }
            }
        }
    }
    else {
        if(pmod == PMod::PATERNAL) {
            if(mFather) {
                paternalSiblings = mFather->children();
            }
            for(Person* sib : paternalSiblings) {
                if(sib->mother() != nullptr && sib->mother() != mMother) {
                    result.insert(sib);
                }
            }
        }
        else if(pmod == PMod::MATERNAL) {
            if(mMother) {
                maternalSiblings = mMother->children();
            }
            for(Person* sib : maternalSiblings) {
                if(sib->father() != nullptr && sib->father() != mFather) {
                    result.insert(sib);
                }
            }
        }
        else {
            if(mFather && mMother) {
                maternalSiblings = mMother->children();
                paternalSiblings = mFather->children();
            }
            for(Person* sib : paternalSiblings) {
                if(sib->mother() != nullptr && sib->mother() != mMother) {
                    result.insert(sib);
                }
            }
            for(Person* sib : maternalSiblings) {
                if(sib->father() != nullptr && sib->father() != mFather) {
                    result.insert(sib);
                }
            }
        }
    }

    result.erase(this);
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

    if(pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if(mMother) {
            std::set<Person*> maternalGrandparents = mMother->parents();
            result.insert(maternalGrandparents.begin(), maternalGrandparents.end());
        }
    }

    if(pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if(mFather) {
            std::set<Person*> paternalGrandparents = mFather->parents();
            result.insert(paternalGrandparents.begin(), paternalGrandparents.end());
        }
    }

    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    std::set<Person*> allGrands = grandparents(pmod);

    for(Person* grand : allGrands) {
        if(grand->gender() == Gender::FEMALE) {
            result.insert(grand);
        }
    }

    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;
    std::set<Person*> allGrands = grandparents(pmod);

    for(Person* grand : allGrands) {
        if(grand->gender() == Gender::MALE) {
            result.insert(grand);
        }
    }

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