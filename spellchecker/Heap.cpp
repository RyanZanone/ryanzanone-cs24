#include "Heap.h"
#include <stdexcept> 

Heap::Heap(size_t capacity) {
    mData = new Entry[capacity];
    mCapacity = capacity;
    mCount = 0;
}

Heap::Heap(const Heap& other) {
    mData = new Entry[other.capacity];
    mCapacity = other.mCapcity;
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

const Entry& Heap::lookup(size_t index) const {
    if(index >= mCount) {
        throw std::out_of_range("Invalid Index");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry entry = mData[0];
    mData[0] = mData[mCount - 1];
    size_t index = 0;

    // perc down
    while(index < mCount) {
        size_t leftChild = index * 2 + 1;
        size_t rightChild = index * 2 + 2;
        size_t minIndex = index;

        if(leftChild < mCount && mData[leftChild].score < mData[minIndex].score) {
            minIndex = leftChild;
        }
        if(rightChild < mCount && mData[rightChild].score < mData[minIndex].score) {
            minIndex = rightChild;
        }

        if(minIndex != index) {
            std::swap(mData[index], mData[minIndex]);
            index = minIndex;
        }
        else {
            break;
        }
    }

    return entry;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if(mcount == 0 || score < mData[0].score) {
        return {value, score};
    }
    Entry entry = pop();
    push(value, score);
    return entry;
}

void Heap::push(const std::string& value, float score) {
    if(mCount >= mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    size_t index = mCount + 1;

    // perc up
    while(index > 0) {
        size_t parent = (index - 1) / 2;
        if(score < mData[parent].score) {
            mData[index] = mData[parent];
            index = parent;
        }
        else {
            break;
        }
    }

    mData[index] = {value, score};
}

const Entry& Heap::top() const {
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}