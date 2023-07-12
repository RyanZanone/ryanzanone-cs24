#ifndef PAUSEVEC_H
#define PAUSEVEC_H

// This provides the size_t type:
#include <cstddef>

class PauseVec
{
  size_t capacity;
  size_t count;

  // Helper Functions

public:
  PauseVec();
  ~PauseVec();

  size_t capacity() const;
  size_t count() const;
  void push();
  int lookup();
  void mutate(size_t idx, int val);
  int remove(size_t idx);
  void remove_val(int val);
};

// Used by the autograder:
PauseVec *create_pausevec();

#endif
