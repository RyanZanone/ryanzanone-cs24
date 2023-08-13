#include "Heap.h"
#include <stdexcept> 

Heap::Heap(size_t capacity) {
    mData = new Entry[capacity];
    mCapacity = capacity;
    mCount = 0;
}

Heap::Heap(const Heap& other) {
    mData = new Entry[other.mCapacity];
    mCapacity = other.mCapacity;
    mCount = other.mCount;

    for(size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}


Heap::Heap(Heap&& other) {
    mData = other.mData;
    mCapacity = other.mCapacity;
    mCount = other.mCount;

    other.mData = nullptr;
    other.mCapacity = 0;
    other.mCount = 0;
}

Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if(index >= mCount) {
        throw std::out_of_range("Invalid Index");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry minEntry = mData[0];
    mData[0] = mData[mCount - 1];
    mCount -= 1;

    size_t currIndex = 0;
    // perc down
    while(true) {
        size_t leftChild = currIndex * 2 + 1;
        size_t rightChild = currIndex * 2 + 2;
        size_t smallest = currIndex;

        if(leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
            smallest = leftChild;
        }
        if(rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
            smallest = rightChild;
        }

        if(smallest != currIndex) {
            std::swap(mData[currIndex], mData[smallest]);
            currIndex = smallest;
        }
        else {
            break;
        }
    }

    return minEntry;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry minEntry = mData[0];
    mData[0].value = value;
    mData[0].score = score;

    size_t currIndex = 0;
    // perc down
    while(true) {
        size_t leftChild = currIndex * 2 + 1;
        size_t rightChild = currIndex * 2 + 2;
        size_t smallest = currIndex;

        if(leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
            smallest = leftChild;
        }
        if(rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
            smallest = rightChild;
        }

        if(smallest != currIndex) {
            std::swap(mData[currIndex], mData[smallest]);
            currIndex = smallest;
        }
        else {
            break;
        }
    }

    return minEntry;
}

void Heap::push(const std::string& value, float score) {
    if(mCount >= mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    size_t index = mCount;
    mData[index].value = value;
    mData[index].score = score;
    mCount += 1;

    // perc up
    while(true) {
        size_t parent = (index - 1) / 2;
        if(score < mData[parent].score) {
            mData[index] = mData[parent];
            index = parent;
        }
        else {
            break;
        }
    }
}

const Heap::Entry& Heap::top() const {
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    else{
        return mData[0];
    }
}