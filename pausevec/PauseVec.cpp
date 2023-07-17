#include "PauseVec.h"

using namespace std;

PauseVec::PauseVec()
{
    arr = new int[1];
    arr[0] = -1;
    size = 1;
    num_items = 0;
    deletions = -1;
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
    if (arr[size - 1] != -1) // if array has no more space
    {
        resize(size * 2);
        arr[size - 1] = val;
        num_items += 1;
        shift(size - 1);
    }
    else
    {
        arr[size - 1] = val;
        num_items += 1;
        shift(size - 1);
    }
}

int PauseVec::lookup(size_t idx)
{
    int temp_idx = idx;
    if (earliest_deletion == -1)
    { // no deletions
        if (idx > num_items - 1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            return arr[idx];
        }
    }
    else if (earliest_deletion < temp_idx)
    { // accessing index above idx
        shift(size - 1);
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
            return arr[idx];
        }
    }
    else
    {
        return arr[idx];
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
        removed_val = arr[idx];
        arr[idx] = -1;
        return removed_val;
    }
    else if (earliest_deletion <= temp_idx && earliest_deletion != -1)
    {
        shift(size - 1);
        if (arr[idx] == -1)
        {
            throw out_of_range("Invalid Index");
        }
        else
        {
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

void PauseVec::shift(size_t end)
{
    for (size_t i = 1; i < end;)
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
        resize(size / 2);
    }
    earliest_deletion = -1;
}