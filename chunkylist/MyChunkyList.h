#ifndef MYCHUNKYLIST_H
#define MYCHUNKYLIST_H

#include "ChunkyList.h"
#include "MyChunkyNode.h"

class MyChunkyList : public ChunkyList
{
private:
  int chunksize;
  int num_items; // number of items, not nodes in list
  MyChunkyNode *head_ref;
  MyChunkyNode *tail_ref;

public:
  MyChunkyList(int chunksize);
  ~MyChunkyList();

  // These functions implement the Sequence abstract data type:
  // See ChunkyList.h for their descriptions.
  int count() const;                               // returns number of items, not nodes in the list
  void insert(int index, const std::string &item); // inserts an item at index, throws std::out_of_range if index is negative or > count()
  std::string &lookup(int index);                  // returns a refernce to the item at index, throws std::out_of_range if there is no such item
  void remove(int index);                          // removes the item at index, throws std::out_of_range if there is no such index

  // These functions are needed by the autograder:
  MyChunkyNode *head() const;
  MyChunkyNode *tail() const;

  // TODO: Add any other member functions you need.
};

#endif
