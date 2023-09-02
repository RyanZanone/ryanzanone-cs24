#ifndef MYGROVE_H
#define MYGROVE_H

#include "StringGrove.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

class MyGrove: public StringGrove<MyGrove> {
private:
  struct Node {
    const char* str;
    int length;
    Node* left;
    Node* right;

    Node(const char* s, int len) {
      str = s;
      length = len;
      left = nullptr;
      right = nullptr;
    }
  };

  Node* root;

public:
  MyGrove(const char* str);

  // Required StringGrove functions.
  // See StringGrove.h for descriptions.
  int     len() const;
  const MyGrove*    concat(MyGrove* other) const;
  char 	  charAt(int index) const;
  const MyGrove*    substr(int start, int end) const;

  // TODO: Add helper functions if necessary.
  char findChar(Node* node, int index) const;
  Node* substringHelper(Node* node, int start, int end) const; 
};

#endif
