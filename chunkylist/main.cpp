#include "ChunkyList.h"
#include <iostream>

// This is an example main file - it won't be graded.
// Use it to interact with your list and make sure it works!

int main() {
  ChunkyList* list = ChunkyList::create(5);

  list->insert(0, "1");
  list->insert(1, "2");
  list->insert(2, "3");
  list->insert(3, "4");
  list->insert(4, "5");
  list->insert(5, "6");
  list->insert(6, "1");
  list->insert(7, "2");
  list->insert(8, "3");
  list->insert(9, "4");
  list->insert(10, "5");
  list->insert(11, "1");
  list->insert(12, "2");
  list->insert(13, "3");
  list->insert(14, "4");


  delete list;
}
