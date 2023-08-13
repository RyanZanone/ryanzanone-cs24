#include "Heap.h"
#include <iostream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main() {
    Heap heap(8);

    heap.push("bears", 3);
    heap.push("pillars", 5);
    heap.push("kings", 3);
    heap.push("apostles", 12);
    heap.push("animals", 12);

    std::cout << heap.pop().value;

    return 0;
}
