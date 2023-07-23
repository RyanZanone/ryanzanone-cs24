#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"
#include <stdexcept>

class MyChunkyNode : public ChunkyNode {
  int num_items; // number of items in the list, not nodes
  int chunksize; 
  std::string *chunk;     // items stored in this node as a C array
  MyChunkyNode *prev_ref; // pointer to the previous node in the list
  MyChunkyNode *next_ref; // pointer to the next node in the array

public:
  MyChunkyNode(int chunksize);  // Constructor
  ~MyChunkyNode(); // Destructor;

  // These functions are needed by the autograder.
  // See ChunkyNode.h for their descriptions.
  int count() const;
  std::string *items() const;
  MyChunkyNode *prev() const;
  MyChunkyNode *next() const;
  void insert(int index, const std::string &item);

  void remove(int index);
  void split();
  void merge();
  void shift_remove(int start);
  void shift_insert(int start);
  void set_next(MyChunkyNode* newnext);
  void set_prev(MyChunkyNode* newprev);

};

#endif
