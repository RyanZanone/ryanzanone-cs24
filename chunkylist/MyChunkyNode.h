#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"

class MyChunkyNode : public ChunkyNode {
private:
  int num_items;          // number of items in the list
  std::string *chunk;     // items stored in this node as a C array
  MyChunkyNode *prev_ref; // pointer to the previous node in the list
  MyChunkyNode *next_ref; // pointer to the next node in the array

public:
  MyChunkyNode();  // Constructor
  ~MyChunkyNode(); // Destructor;

  // These functions are needed by the autograder.
  // See ChunkyNode.h for their descriptions.
  int count() const;
  std::string *items() const;
  MyChunkyNode *prev() const;
  MyChunkyNode *next() const;
  void insert(int index, const std::string &item);

  void split();
  void merge();
};

#endif
