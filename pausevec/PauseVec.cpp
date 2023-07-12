#include "PauseVec.h"

using namespace std;

PauseVec::PauseVec()
{
    arr = new int[1];
    size = 1;
    num_items = 0;
}

PauseVec::~PauseVec()
{
    delete[] arr;
}

size_t PauseVec::capacity() const
{
    return size;
}

size_t PauseVec::count() const
{
    return num_items;
}

void PauseVec::push(int val)
{
}

int PauseVec::lookup(size_t idx)
{
    return 1111;
}

void PauseVec::mutate(size_t idx, int val)
{
}

int PauseVec::remove(size_t idx)
{
    return 1111;
}

void PauseVec::remove_val(int val)
{
}

PauseVec *create_pausevec()
{
    return new PauseVec;
}