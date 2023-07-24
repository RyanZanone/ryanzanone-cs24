#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"
#include "Node.cpp"
#include <stdexcept>

class MyStack: public Stack {
  int count;
  Node* topnode;

public:
  // TODO: Constructor & Destructor
  MyStack();
  ~MyStack();

  // Required Stack functions.
  // See Stack.h for descriptions.
  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;

  // TODO: Add helper functions if necessary.
};

#endif
