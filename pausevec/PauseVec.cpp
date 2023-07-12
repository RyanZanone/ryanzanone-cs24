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
    if (size - num_items == 0)
    {
        int *temp_arr = new int[size * 2];
        for (size_t i = 0; i < size; i++)
        {
            temp_arr[i] = arr[i];
        }
        delete arr;
        arr = temp_arr;
        delete temp_arr;
        size = size * 2;
    }
    arr[size - num_items - 1] = val;
    num_items += 1;
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