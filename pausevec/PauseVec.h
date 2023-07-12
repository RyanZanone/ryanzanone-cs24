#ifndef PAUSEVEC_H
#define PAUSEVEC_H

// This provides the size_t type:
#include <cstddef>

class PauseVec
{
  int *arr;
  size_t size;
  size_t num_items;

  // Helper Functions

public:
  PauseVec();
  ~PauseVec();

  size_t capacity() const;
  size_t count() const;
  void push(int val);
  int lookup(size_t idx);
  void mutate(size_t idx, int val);
  int remove(size_t idx);
  void remove_val(int val);
};

// Used by the autograder:
PauseVec *create_pausevec();

#endif
