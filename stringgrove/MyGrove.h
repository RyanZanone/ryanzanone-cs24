#ifndef MYGROVE_H
#define MYGROVE_H

#include "StringGrove.h"

class MyGrove: public StringGrove<MyGrove> {
  // TODO: Member Variables
public:
  MyGrove();
  MyGrove(const char* str);

  // Required StringGrove functions.
  // See StringGrove.h for descriptions.
  int     len() const;
  MyGrove*    concat(MyGrove* other) const;
  char 	  charAt(int index) const;
  MyGrove*    substr(int start, int end) const;

  // TODO: Add helper functions if necessary.
};

#endif
