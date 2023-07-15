#include "PauseVec.h"

using namespace std;

PauseVec::PauseVec()
{
    arr = new int[1];
    size = 1;
    num_items = 0;
    deletions = 0;
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
        resize(size * 2);
    }
    arr[size - num_items - 1] = val;
    num_items += 1;
}

int PauseVec::lookup(size_t idx)
{
    if (idx > size - 1)
    {
        throw out_of_range("Invalid Index");
    }
    else if (idx < deletions)
    {
        shift(0, idx - 1, -1);
        deletions = idx;
    }

    return arr[idx];
}

void PauseVec::mutate(size_t idx, int val)
{
    if (idx >= num_items)
    {
        throw out_of_range("Index out of range");
    }

    if (idx < deletions)
    {
        shift(0, idx - 1, -1);
        deletions = idx;
    }

    arr[idx] = idx;
}

int PauseVec::remove(size_t idx)
{
    if (idx >= num_items)
    {
        throw out_of_range("Index out of range");
    }

    if (idx < deletions)
    {
        shift(0, idx - 1, -1);
        deletions = idx;
    }

    int value = arr[idx];
    shift(idx + 1, num_items - 1, -1);
    num_items--;

    if (num_items <= size / 4)
    {
        resize(size / 2);
    }

    return value;
}

void PauseVec::remove_val(int val)
{
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < num_items; read_idx++)
    {
        if (arr[read_idx] != val)
        {
            arr[write_idx++] = arr[read_idx];
        }
    }

    num_items = write_idx;

    if (num_items <= size / 4)
    {
        resize(size / 2);
    }
}

PauseVec *create_pausevec()
{
    return new PauseVec;
}

void PauseVec::resize(size_t new_size)
{
    int *temp_arr = new int[new_size];
    for (size_t i = 0; i < size; i++)
    {
        temp_arr[i] = arr[i];
    }
    delete[] arr;
    arr = temp_arr;
    delete[] temp_arr;
    size = new_size;
    deletions = 0;
}

void PauseVec::shift(size_t start, size_t end, int shift)
{
    for (size_t i = start; i <= end; i++)
    {
        arr[i + shift] = arr[i];
    }
}