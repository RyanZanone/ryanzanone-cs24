#include "ChunkyList.h"
#include <iostream>

// This is an example main file - it won't be graded.
// Use it to interact with your list and make sure it works!

int main() {
  ChunkyList* list = ChunkyList::create(5);

  list->insert(0, "1");
  std::cout << list->lookup(0) << std::endl;
  list->remove(0);
  std::cout << list->lookup(0) << std::endl;

  delete list;
}
