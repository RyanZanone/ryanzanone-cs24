#include "PauseVec.h"

using namespace std;

PauseVec::PauseVec()
{
    arr = new int[1];
    arr[0] = -1;
    size = 1;
    num_items = 0;
    earliest_deletion = -1; // set to size by default and after resizing/shifting
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
    if (size - num_items == 0) // if array is full
    {
        this->resize(size * 2);
        arr[num_items] = val;
        num_items += 1;
    }
    else if (arr[size - 1] != -1)
    {
        this->shift();
        arr[num_items] = val;
        num_items += 1;
    }
    else
    {
        arr[size - 1] = val;
        this->shift();
        num_items += 1;
    }
}

int PauseVec::lookup(size_t idx)
{
    int temp_idx = idx;
    if (earliest_deletion == -1)
    { // no deletions
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            return arr[idx];
        }
    }
    else if (earliest_deletion > temp_idx)
    {
        return arr[idx];
    }
    else
    {
        this->shift();
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            return arr[idx];
        }
    }
}

void PauseVec::mutate(size_t idx, int val)
{
}

int PauseVec::remove(size_t idx)
{
    int temp_idx = idx;
    int removed_val;
    if (idx > size - 1)
    {
        throw out_of_range("Invalid Index");
    }
    else if (earliest_deletion > temp_idx)
    {
        earliest_deletion = idx;
        num_items -= 1;
        removed_val = arr[idx];
        arr[idx] = -1;
        return removed_val;
    }
    else if (earliest_deletion <= temp_idx && earliest_deletion != -1)
    {
        this->shift();
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            num_items -= 1;
            removed_val = arr[idx];
            arr[idx] = -1;
            return removed_val;
        }
    }
    else
    {
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            earliest_deletion = idx;
            num_items -= 1;
            removed_val = arr[idx];
            arr[idx] = -1;
            return removed_val;
        }
    }
}

void PauseVec::remove_val(int val)
{
}

PauseVec *create_pausevec()
{
    return new PauseVec;
}

void PauseVec::resize(size_t new_size)
{
    int *temp_arr = new int[new_size];
    for (size_t i = 0; i < new_size; i++)
    {
        temp_arr[i] = -1;
    }
    for (size_t i = 0; i < size; i++)
    {
        temp_arr[i] = arr[i];
    }
    delete[] arr;
    arr = temp_arr;
    size = new_size;
}

void PauseVec::shift()
{
    for (size_t i = 1; i < size;)
    {
        if (arr[i - 1] < 0)
        {
            arr[i - 1] = arr[i];
            arr[i] = -1;
            if (i != 1 && arr[i - 2] < 0)
            {
                i--;
                continue;
            }
        }
        i++;
        continue;
    }
    if (num_items == size / 2)
    {
        this->resize(size / 2);
    }
    earliest_deletion = -1;
}