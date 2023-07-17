#ifndef PAUSEVEC_H
#define PAUSEVEC_H

// This provides the size_t type:
#include <cstddef>
#include <stdexcept>

class PauseVec
{
private:
  int *arr;
  size_t size;
  size_t num_items;
  size_t deletion;
  int deletions;

  void resize(size_t new_size);
  void shift(size_t end);

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
