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

  MyGrove* str4 = new MyGrove("Hello, World!");
  const MyGrove* substring = str4->substr(7, 12); // Should be "World!"
  std::cout << "Substring: ";
  for (int i = 0; i < substring->len(); ++i) {
      std::cout << substring->charAt(i);
  }
  std::cout << std::endl;

    MyGrove* str3 = new MyGrove("Testing");
  try {
      char charAtIndex = str3->charAt(10);
      std::cout << "Character at index 10: " << charAtIndex << std::endl;
  } 
  catch (const std::out_of_range& e) {
      std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
