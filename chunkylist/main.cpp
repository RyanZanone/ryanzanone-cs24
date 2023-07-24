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
  list->insert(15, "16");
  list->insert(16, "17");
  list->insert(17, "18");
  list->insert(18, "19");
  list->insert(19, "20");

  
  list->remove(5);
  list->remove(10);
  list->remove(15);
  list->remove(8);
  list->remove(12);


  list->remove(7);
  list->remove(7);
  list->remove(8);

  cout << list->lookup(5) << endl;
  cout << list->lookup(8) << endl;
  cout << list->lookup(11) << endl;
  cout << list->count() << endl;
  cout << list->head()->count() << endl;
  cout << list->head()->next()->count() << endl;
  cout << list->head()->next()->next()->count() << endl;
  cout << list->head()->next()->next()->next()->count() << endl;

  delete list;
}
