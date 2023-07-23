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

    if (prev_ref != nullptr) {
        prev_ref->next_ref = next_ref;
    }

    if (next_ref != nullptr) {
        next_ref->prev_ref = prev_ref;
    }
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
        if(index > num_items) {
            index -= num_items;
            next_ref->insert(index, item);
        }
        else if (chunk[index] == "") {
            chunk[index] = item;
            num_items += 1;
        }
        else {
            shift_insert(index);
            chunk[index];
            num_items += 1;
        }
    }
    else if (chunk[index] == "") {
        chunk[index] = item;
        num_items += 1;
    }
    else {
        shift_insert(index);
        chunk[index] = item;
        num_items += 1;
    }
}

void MyChunkyNode::remove(int index) {
    if(index == num_items - 1) { // deleting last item, no shifting
        chunk[chunksize - 1] = "";
        num_items -= 1;
    }
    else {
        shift_remove(index);
        chunk[index] = "";
        num_items -= 1;
    }
    if(num_items <= chunksize / 2) { // node is empty
        merge();
    } 
}

void MyChunkyNode::split() {
    // Create new node
    MyChunkyNode* newnode = new MyChunkyNode(chunksize);
    // Update linked list pointers
    newnode->prev_ref = this;
    newnode->next_ref = next_ref;
    if(next_ref != nullptr) {
        next_ref->prev_ref = newnode;
    }
    next_ref = newnode;
    // Copy over data
    int splitindex = chunksize / 2;
    if(num_items % 2 == 0) { // even number of items, make both have the same amount
        for(int i = splitindex; i < chunksize; i++) {
            newnode->insert(i, chunk[i]);
            remove(i);
        }
    }
    else {
        for(int i = splitindex + 1; i < chunksize; i++) {
            newnode->insert(i, chunk[i]);
            remove(i);
        }
    }
}

void MyChunkyNode::merge() {
    if(prev_ref->count() <= chunksize / 2) {
        // transfer previous node's data to current node
        int mergeindex = chunksize / 2;
        for (int i = mergeindex; i < chunksize; i++) {
            insert(i, prev_ref->chunk[i]);
        }
        // update linked list pointers
        if (prev_ref->prev_ref != nullptr) {
            prev_ref->prev_ref->next_ref = this;
        }
        prev_ref = prev_ref->prev_ref;
    }
    else if (next_ref->count() <= chunksize / 2) {
        int mergeindex = chunksize / 2;
        for (int i = mergeindex; i < chunksize; i++) {
            insert(i, next_ref->chunk[i]);
        }
        // update linked list pointers
        if (next_ref->next_ref != nullptr) {
            next_ref->next_ref->prev_ref = this;
        }
        next_ref = next_ref->next_ref;
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

void MyChunkyNode::set_next(MyChunkyNode* newnext) {
    next_ref = newnext;
}

void MyChunkyNode::set_prev(MyChunkyNode* newprev) {
    prev_ref = newprev;
}
