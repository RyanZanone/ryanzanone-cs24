#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode() {
    chunk = new std::string;
    prev_ref = nullptr;
    next_ref = nullptr;
    num_items = 0;
}

MyChunkyNode::~MyChunkyNode() {
    delete[] chunk;
}

int MyChunkyNode::count() const {
    return num_items;
}

std::string* MyChunkyNode::items() const {
    return chunk;
}

MyChunkyNode* MyChunkyNode::prev() const {
    return prev_ref;
}

MyChunkyNode* MyChunkyNode::next() const {
    return next_ref;
}

void MyChunkyNode::insert(int index, const std::string &item) {
    chunk[index] = item;
    num_items += 1;
}

void MyChunkyNode::split() {
    // Create new nodes
    MyChunkyNode* half1 = new MyChunkyNode;
    MyChunkyNode* half2 = new MyChunkyNode;
    // Restructure List w/ node references
    half1->prev_ref = this->prev_ref;
    half1->next_ref = half2;
    half2->prev_ref = half1;
    half2->next_ref = this->next_ref;

}