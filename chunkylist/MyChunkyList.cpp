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
}

std::string& MyChunkyList::lookup(int index) {

}

void MyChunkyList::remove(int index) {

}


