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
    for(int i = chunksize - 1; i > index; i--) {
        std::string tempitem =  chunk[i - 1];
        chunk[i - 1] = "";
        chunk[i] = tempitem;
    }
    chunk[index] = item;
    num_items += 1;
}

void MyChunkyNode::split_insert(int index, const std::string &item) {
    // Create new node
    MyChunkyNode* newnode = new MyChunkyNode(chunksize);
    MyChunkyNode* tempnode = new MyChunkyNode(chunksize + 1);
    // Update linked list pointers
    newnode->prev_ref = this;
    newnode->next_ref = next_ref;
    if(next_ref != nullptr) {
        next_ref->prev_ref = newnode;
    }
    next_ref = newnode;
    // Copy data over to tempnode
    for(int i = 0; i < chunksize; i++) {
        tempnode->insert(i, chunk[i]);
    }
    // Insert item into proper position in tempnode
    tempnode->insert(index, item);
    // Copy data over to other two nodes
    int splitindex = (chunksize + 2) / 2;
    for(int i = 0; i < chunksize; i++) { // remove all items from original node
        chunk[i] = "";
        num_items -= 1;
    }
    for(int i = 0; i < splitindex; i++) { // copy over to original node
        insert(i, tempnode->items()[i]);
    }
    for(int i = splitindex; i < chunksize + 1; i++) { // copy over to new node
        newnode->insert(i - splitindex, tempnode->items()[i]);
    }
    delete tempnode;
}

void MyChunkyNode::remove(int index) {
    chunk[index] = "";
    num_items -= 1;
    for(int i = 0; i < chunksize - 1; i++) {
        if(chunk[i] == "") {
            chunk[i] = chunk[i + 1];
            chunk[i + 1] = "";
        }
    }
    if(num_items == 0) { // empty node, change pointers and prepare for deletion
        if(prev_ref != nullptr) {
            prev_ref->next_ref = next_ref;
        }
        if(next_ref != nullptr) {
            next_ref->prev_ref = prev_ref;
        }
        delete this;
    }
}

void MyChunkyNode::merge_prev() {
    // copy over items from current node to prev node
    for(int i = 0; i < prev_ref->count(); i++) {
        insert(i, prev_ref->items()[i]);
    }
    // update ll pointers
    MyChunkyNode* tempnode = prev_ref;
    prev_ref = prev_ref->prev_ref;
    // delete prev node;
    delete tempnode;
}

void MyChunkyNode::merge_next() {
    // copy over items from next node to current node
    for(int i = 0; i < next_ref->num_items; i++) {
        insert(num_items + i, next_ref->chunk[i]);
    }
    // update ll pointers
    MyChunkyNode* tempnode = next_ref;
    next_ref = next_ref->next_ref;
    // delete next node
    delete tempnode;
}

void MyChunkyNode::set_next(MyChunkyNode* newnext) {
    next_ref = newnext;
}

void MyChunkyNode::set_prev(MyChunkyNode* newprev) {
    prev_ref = newprev;
}

