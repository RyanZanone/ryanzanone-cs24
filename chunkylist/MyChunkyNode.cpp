#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(int chunksize) {
    chunk = new std::string[chunksize];
    this->chunksize = chunksize;
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
    if(num_items == chunksize) { // node is full
        split();
    }
    else if(chunk[index] != "") {
        shift_insert(index);
        chunk[index] = item;
        num_items += 1;
    }
    else {
        chunk[index] = item;
        num_items += 1;
    }
}

void MyChunkyNode::split() {
    // Create new nodes
    MyChunkyNode* half1 = new MyChunkyNode(chunksize);
    MyChunkyNode* half2 = new MyChunkyNode(chunksize);
    // Restructure node order
    half1->prev_ref = this->prev_ref;
    half1->next_ref = half2;
    half2->prev_ref = half1;
    half2->next_ref = this->next_ref;
    // transfer over data

}

void MyChunkyNode::merge() {
    if(prev_ref->count() <= chunksize / 2) {

    }
    else if(next_ref->count() <= chunksize / 2) {

    }

}

void MyChunkyNode::shift_remove(int start) {
    for(int i = start; i < chunksize - 1; i++) {
        std::string tempitem = chunk[i + 1];
        chunk[i + 1] = "";
        chunk[i] = tempitem;
    }
}

void MyChunkyNode::shift_insert(int start) {
    for(int i = chunksize - 1; i > start; i--) {
        std::string tempitem =  chunk[i - 1];
        chunk[i - 1] = "";
        chunk[i] = tempitem;
    }
}