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
        std::set<Person*> maternalSiblings = mMother->siblings(pmod, smod);
        result.insert(maternalSiblings.begin(), maternalSiblings.end());
    }

    if (mFather) {
        std::set<Person*> paternalSiblings = mFather->siblings(pmod, smod);
        result.insert(paternalSiblings.begin(), paternalSiblings.end());
    }

    return result;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (smod == SMod::FULL || smod == SMod::ANY) {
        if (mMother != nullptr) {
            std::set<Person*> maternalSiblings = mMother->siblings(pmod, SMod::FULL);
            result.insert(maternalSiblings.begin(), maternalSiblings.end());
        }

        if (mFather != nullptr) {
            std::set<Person*> paternalSiblings = mFather->siblings(pmod, SMod::FULL);
            result.insert(paternalSiblings.begin(), paternalSiblings.end());
        }
    }

    if (smod == SMod::HALF || smod == SMod::ANY) {
        if (mMother != nullptr) {
            std::set<Person*> maternalHalfSiblings = mMother->siblings(pmod, SMod::HALF);
            result.insert(maternalHalfSiblings.begin(), maternalHalfSiblings.end());
        }

        if (mFather != nullptr) {
            std::set<Person*> paternalHalfSiblings = mFather->siblings(pmod, SMod::HALF);
            result.insert(paternalHalfSiblings.begin(), paternalHalfSiblings.end());
        }
    }

    // Remove self from result
    result.erase(this);

    return result;
}

std::set<Person*> Person::children() {
    std::set<Person*> result;

    for (Person* person : mChildren) {
        result.insert(person);
    }

    return result;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> result;

    std::set<Person*> parents = this->parents(pmod);
    for (Person* parent : parents) {
        std::set<Person*> siblings = parent->siblings(pmod, smod);
        for (Person* sibling : siblings) {
            std::set<Person*> children = sibling->children();
            result.insert(children.begin(), children.end());
        }
    }

    // Remove self from result
    result.erase(this);

    return result;
}

std::set<Person*> Person::daughters() {
    std::set<Person*> result;

    std::set<Person*> children = this->children();
    for (Person* child : children) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }

    return result;
}

std::set<Person*> Person::descendants() {
    std::set<Person*> result;

    std::set<Person*> children = this->children();
    result.insert(children.begin(), children.end());

    for (Person* child : children) {
        std::set<Person*> childDescendants = child->descendants();
        result.insert(childDescendants.begin(), childDescendants.end());
    }

    return result;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;

    std::set<Person*> children = this->children();
    for (Person* child : children) {
        std::set<Person*> childChildren = child->children();
        result.insert(childChildren.begin(), childChildren.end());
    }

    return result;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;

    std::set<Person*> grandchildrenSet = this->grandchildren();
    for (Person* grandchild : grandchildrenSet) {
        if (grandchild->gender() == Gender::FEMALE) {
            result.insert(grandchild);
        }
    }

    return result;
}

std::set<Person*> Person::grandsons() {
    std::set<Person*> result;

    std::set<Person*> grandchildrenSet = this->grandchildren();
    for (Person* grandchild : grandchildrenSet) {
        if (grandchild->gender() == Gender::MALE) {
            result.insert(grandchild);
        }
    }

    return result;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;

    if (mFather != nullptr) {
        result.insert(mFather->father());
    }

    if (mMother != nullptr && pmod != PMod::PATERNAL) {
        result.insert(mMother->father());
    }

    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;

    if (mFather != nullptr) {
        result.insert(mFather->mother());
    }

    if (mMother != nullptr && pmod != PMod::PATERNAL) {
        result.insert(mMother->mother());
    }

    return result;
}

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother != nullptr) {
            std::set<Person*> maternalGrandparents = mMother->parents();
            result.insert(maternalGrandparents.begin(), maternalGrandparents.end());
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather != nullptr) {
            std::set<Person*> paternalGrandparents = mFather->parents();
            result.insert(paternalGrandparents.begin(), paternalGrandparents.end());
        }
    }

    return result;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            std::set<Person*> maternalBrothers = mMother->brothers(PMod::ANY, smod);
            for (Person* uncle : maternalBrothers) {
                result.insert(uncle->sons().begin(), uncle->sons().end());
            }
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            std::set<Person*> paternalBrothers = mFather->brothers(PMod::ANY, smod);
            for (Person* uncle : paternalBrothers) {
                result.insert(uncle->sons().begin(), uncle->sons().end());
            }
        }
    }

    return result;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            std::set<Person*> maternalSisters = mMother->sisters(PMod::ANY, smod);
            for (Person* aunt : maternalSisters) {
                result.insert(aunt->daughters().begin(), aunt->daughters().end());
            }
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            std::set<Person*> paternalSisters = mFather->sisters(PMod::ANY, smod);
            for (Person* aunt : paternalSisters) {
                result.insert(aunt->daughters().begin(), aunt->daughters().end());
            }
        }
    }

    return result;
}

std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            result.insert(mMother);
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            result.insert(mFather);
        }
    }

    return result;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            std::set<Person*> maternalSiblings = mMother->siblings(PMod::ANY, smod);
            result.insert(maternalSiblings.begin(), maternalSiblings.end());
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            std::set<Person*> paternalSiblings = mFather->siblings(PMod::ANY, smod);
            result.insert(paternalSiblings.begin(), paternalSiblings.end());
        }
    }

    return result;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            std::set<Person*> maternalSisters = mMother->sisters(PMod::ANY, smod);
            result.insert(maternalSisters.begin(), maternalSisters.end());
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            std::set<Person*> paternalSisters = mFather->sisters(PMod::ANY, smod);
            result.insert(paternalSisters.begin(), paternalSisters.end());
        }
    }

    return result;
}

std::set<Person*> Person::sons() {
    std::set<Person*> result;
    for (Person* child : mChildren) {
        if (child->gender() == Gender::MALE) {
            result.insert(child);
        }
    }
    return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;

    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mMother) {
            std::set<Person*> maternalSiblings = mMother->siblings(PMod::ANY, smod);
            for (Person* uncle : maternalSiblings) {
                if (uncle->gender() == Gender::MALE) {
                    result.insert(uncle);
                }
            }
        }
    }

    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (mFather) {
            std::set<Person*> paternalSiblings = mFather->siblings(PMod::ANY, smod);
            for (Person* uncle : paternalSiblings) {
                if (uncle->gender() == Gender::MALE) {
                    result.insert(uncle);
                }
            }
        }
    }

    return result;
}

