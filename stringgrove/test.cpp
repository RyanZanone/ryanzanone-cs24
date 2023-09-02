#include "MyGrove.h"
#include <iostream>

// Use this file to test your MyGrove class!
// This file won't be graded - do whatever you want.

int main() {
  MyGrove* str1 = new MyGrove("Hello");
  MyGrove* str2 = new MyGrove(" World");
  const MyGrove* concatenated = str1->concat(str2);
  std::cout << "Concatenated String: ";
  for (int i = 0; i < concatenated->len(); ++i) {
    std::cout << concatenated->charAt(i);
  }
  std::cout << std::endl;

  MyGrove* str = new MyGrove("Testing");
  char charAtIndex = str->charAt(2); // Should be 's'
  std::cout << "Character at index 2: " << charAtIndex << std::endl;


  MyGrove* str3 = new MyGrove("Hello, World!");
  const MyGrove* substring = str3->substr(7, 12); // Should be "World!"
  std::cout << "Substring: ";
  
  if(substring) {
    std::cout << "Substring length: " << substring->len() << std::endl;
  }
  else {
    std::cerr << "Substring is null." << std::endl;
  }

  return 0;
}
