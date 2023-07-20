#include "MyChunkyList.h"

MyChunkyList::MyChunkyList(int chunksize) {
    this->chunksize = chunksize;
    num_items = 0;
    num_nodes = 0;
    head_ref = nullptr;
    tail_ref = nullptr;
}

MyChunkyList::~MyChunkyList() {
    delete head_ref;
    delete tail_ref;
}

int MyChunkyList::count() const {
    return num_items;
}

MyChunkyNode* MyChunkyList::head() const {
    return head_ref;
}

MyChunkyNode* MyChunkyList::tail() const {
    return tail_ref;
}

void MyChunkyList::insert(int index, const std::string &item) {
    if(index < 0 || index > this->count()) {
        throw std::out_of_range("Invalid Index");
    }
    else if (head_ref == nullptr && index > chunksize - 1) { // list is empty, but no such index is available
        throw std::out_of_range("Invalid Index");
    }
    else if (head_ref == nullptr) { // list is empty, index is valid
        MyChunkyNode* newnode = new MyChunkyNode(chunksize);
        head_ref = newnode;
        tail_ref = newnode;
        newnode->insert(index, item);
        num_items += 1;
    }
    else if (index == 0 && head_ref->count() == chunksize) { // inserting at beginning and node is full
        MyChunkyNode *newnode = new MyChunkyNode(chunksize);
        tail_ref = newnode;
        newnode->insert(0, item);
        num_items += 1;
    }
    else if (index == num_items - 1 && tail_ref->count() == chunksize) { // inserting at end and node is full
        MyChunkyNode *newnode = new MyChunkyNode(chunksize);
        tail_ref = newnode;
        newnode->insert(0, item);
        num_items += 1;
    }
    else {
        MyChunkyNode *currnode = head_ref;
        int listindex = 0;
        int nodeindex = 0;
        
        while(listindex != index && currnode != nullptr) { // iterate through to find which node index is in
            listindex += 1;
            if(nodeindex == chunksize - 1) { // reached the end of the current node
                currnode = currnode->next(); // move onto next node
                nodeindex = 0; // reset node index
            }
            else {
                nodeindex += 1;
            }
        }
        currnode->insert(index, item);
        num_items += 1;
    }
}

std::string& MyChunkyList::lookup(int index) {
    MyChunkyNode *currnode = head_ref;
    int listindex = 0;
    int nodeindex = 0;
    
    while(listindex != index && currnode != nullptr) {
        listindex += 1;
        if(nodeindex == chunksize - 1) {
            currnode = currnode->next();
            nodeindex = 0;
        }
        else {
            nodeindex += 1;
        }
    }

    if (currnode == nullptr) { // reached end of list, no such index
        throw std::out_of_range("Invalid Index");
    }
    else if (currnode->items()[nodeindex] == "") { // empty string, no such item
        throw std::out_of_range("Invalid Index");
    }
    else {
        return currnode->items()[nodeindex];
    }
        
}

void MyChunkyList::remove(int index) {
    MyChunkyNode *currnode = head_ref;
    int listindex = 0;
    int nodeindex = 0;
    
    while(listindex != index && currnode != nullptr) {
        listindex += 1;
        if(nodeindex == chunksize - 1) {
            currnode = currnode->next();
            nodeindex = 0;
        }
        else {
            nodeindex += 1;
        }
    }

    if(currnode == nullptr) {
        throw std::out_of_range("Invalid Index");
    }
    else if(currnode->items()[nodeindex] == "") {
        throw std::out_of_range("Invalid Index");
    }
    else {
        currnode->items()[nodeindex] = ""; // remove item
        currnode->shift_remove(nodeindex);
        if(currnode->count() <= chunksize / 2) {
            currnode->merge();
        }
    }
}

void MyChunkyList::set_tail(MyChunkyNode* new_tail) {
    tail_ref = new_tail;
}

