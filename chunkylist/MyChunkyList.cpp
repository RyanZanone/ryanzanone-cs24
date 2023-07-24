#include "MyChunkyList.h"

MyChunkyList::MyChunkyList(int chunksize) {
    this->chunksize = chunksize;
    num_items = 0;
    head_ref = nullptr;
    tail_ref = nullptr;
}

MyChunkyList::~MyChunkyList() {
    MyChunkyNode* current = head_ref;
    while (current != nullptr) {
        MyChunkyNode* next = current->next();
        delete current;
        current = next;
    }
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
    if(index < 0 || index > num_items) {
        throw std::out_of_range("Invalid Index");
    }
    else if (head_ref == nullptr) { // list is empty
        MyChunkyNode* newnode = new MyChunkyNode(chunksize);
        head_ref = newnode;
        tail_ref = newnode;
        head_ref->insert(0, item);
        num_items += 1;
    }
    else if (index == 0 && head_ref->count() == chunksize) { // inserting at beginning and node is full
        MyChunkyNode *newnode = new MyChunkyNode(chunksize);
        newnode->insert(0, item);
        newnode->set_next(head_ref);
        head_ref->set_prev(newnode);
        head_ref = newnode;
        num_items += 1;
    }
    else if (index == num_items && tail_ref->count() == chunksize) { // inserting at end and node is full
        MyChunkyNode *newnode = new MyChunkyNode(chunksize);
        newnode->insert(0, item);
        tail_ref->set_next(newnode);
        newnode->set_prev(tail_ref);
        tail_ref = newnode;
        num_items += 1;
    }
    else {
        MyChunkyNode *currnode = head_ref;
        int listindex = 0;
        int nodeindex = 0;
        
        while(listindex != index && currnode != nullptr) { // iterate through to find which node index is in
            if(currnode->items()[nodeindex] != "") {
                listindex += 1;
            }
            if(nodeindex == chunksize - 1) { // reached the end of the current node
                currnode = currnode->next(); // move onto next node
                nodeindex = 0; // reset node index
            }
            else {
                nodeindex += 1;
            }
        }

        if (currnode->count() == chunksize) { // if the node is full after finding the correct node
            currnode->split_insert(nodeindex, item);
        } 
        else {
            currnode->insert(nodeindex, item);
        }
        num_items += 1;
    }
    if(tail_ref->next() != nullptr) {
        tail_ref = tail_ref->next();
    }
}

std::string& MyChunkyList::lookup(int index) {
    if(index > num_items - 1 || index < 0) {
        throw std::out_of_range("Invalid Index");
    }

    MyChunkyNode *currnode = head_ref;
    int listindex = 0;
    int nodeindex = 0;
    
    while(listindex != index && currnode != nullptr) {
        if (currnode->items()[nodeindex] != "" && nodeindex != chunksize - 1) {
            nodeindex += 1;
        }
        else {
            currnode = currnode->next();
            nodeindex = 0;
        }
        if(currnode->items()[nodeindex] != "") {
            listindex += 1;
        }
    }
    if(currnode == nullptr) {
        throw std::out_of_range("Invalid Index");
    }

    return currnode->items()[nodeindex];
        
}

void MyChunkyList::remove(int index) {
    if(index > num_items - 1 || index < 0) {
        throw std::out_of_range("Invalid Index");
    }

    MyChunkyNode *currnode = head_ref;
    int listindex = 0;
    int nodeindex = 0;
    
    while(listindex != index && currnode != nullptr) {
        if (currnode->items()[nodeindex] != "" && nodeindex != chunksize - 1) {
            nodeindex += 1;
        }
        else {
            currnode = currnode->next();
            nodeindex = 0;
        }
        if(currnode->items()[nodeindex] != "") {
            listindex += 1;
        }
    }

    if(currnode == nullptr) {
        throw std::out_of_range("Invalid Index");
    }
    else if(head_ref == tail_ref && currnode == head_ref && currnode->count() == 1) {
        delete currnode;
        num_items -= 1;
        head_ref = nullptr;
        tail_ref = nullptr;
    }
    else if(currnode == head_ref && currnode->count() == 1) {
        head_ref = currnode->next();
        currnode->remove(nodeindex);
        num_items -= 1;
    }
    else if(currnode == tail_ref && currnode->count() == 1) {
        tail_ref = currnode->prev();
        currnode->remove(nodeindex);
        num_items -= 1;
    }
    else {
        currnode->remove(nodeindex);
        num_items -= 1;
        if(currnode->next() == nullptr) {
            tail_ref = currnode;
        }
        if(currnode->prev() == nullptr) {
            head_ref = currnode;
        }
    }
}


