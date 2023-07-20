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
    // Create new node
    MyChunkyNode* newnode = new MyChunkyNode(chunksize);
    // Restructure node order
    newnode->prev_ref = this;
    newnode->next_ref = this->next_ref;
    // transfer over data
    int splitindex = num_items / 2;
    int remaining_items = num_items - splitindex;
    for(int i = splitindex; i < num_items; i++) {
        newnode->insert(i - splitindex, chunk[i]);
        chunk[i] = "";
        num_items -= 1;
    }
}

void MyChunkyNode::merge() {
    if(prev_ref->count() <= chunksize / 2) {
        int mergeindex = chunksize / 2;
        for (int i = mergeindex; i < chunksize; i++) {
            chunk[i] = prev_ref->chunk[chunksize - mergeindex];
        }
        prev_ref->prev_ref->next_ref = this;
        MyChunkyNode* tempnode = prev_ref;
        prev_ref = prev_ref->prev_ref;
        delete[] tempnode;
    }
    else if(next_ref->count() <= chunksize / 2) {
        int mergeindex = chunksize / 2;
        for (int i = mergeindex; i < chunksize; i++) {
            chunk[i] = next_ref->chunk[chunksize - mergeindex];
        }
        next_ref->next_ref->prev_ref = this;
        MyChunkyNode* tempnode = next_ref;
        next_ref = next_ref->next_ref;
        delete[] tempnode;
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

void MyChunkyNode::list_restructure(MyChunkyNode* currnode) {

}