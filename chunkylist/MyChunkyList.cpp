#include "MyChunkyList.h"

MyChunkyList::MyChunkyList(int chunksize)
{
    this->chunksize = chunksize;
    num_items = 0;
    head_ref = nullptr;
    tail_ref = nullptr;
}

MyChunkyList::~MyChunkyList()
{
    delete head_ref;
    delete tail_ref;
}

int MyChunkyList::count() const
{
    return num_items;
}
