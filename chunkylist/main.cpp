#include "ChunkyList.h"
#include <iostream>

// This is an example main file - it won't be graded.
// Use it to interact with your list and make sure it works!

using namespace std;

int main() {
  ChunkyList* list = ChunkyList::create(5);

  list->insert(0, "1");
  list->insert(1, "2");
  list->insert(2, "3");
  list->insert(3, "4");
  list->insert(4, "5");
  list->insert(5, "6");
  list->insert(6, "7");
  list->insert(7, "8");
  list->insert(8, "9");
  list->insert(9, "10");
  list->insert(10, "11");
  list->insert(11, "12");
  list->insert(12, "13");
  list->insert(13, "14");
  list->insert(14, "15");
  
  cout << list->lookup(4) << endl;
  list->remove(3);
  cout << list->lookup(3) << endl;
  cout << list->lookup(5) << endl;
  cout << list->lookup(4) << endl;

  delete list;
}
