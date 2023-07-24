#include "Stack.h"
#include "MyStack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

bool is_operator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~";
}

double operation(const std::string& op, double num1, double num2) {
  if(op == "+") {
    return num1 + num2;
  }
  if(op == "-") {
    return num1 - num2;
  }
  if(op == "*") {
    return num1 * num2;
  }
  if(op == "/") {
    return num1 / num2;
  }
  if(op == "%") {
    return fmod(num1, num2);
  }
  if(op == "^") {
    return pow(num1, num2);
  }
  if(op == "~") {
    return -num1;
  }
  return 0;
}

int main() {
  
  std::string input;
  getline(std::cin, input); // store line of input as a stirng in input
  MyStack Stack;

  std::stringstream ss(input);
  std::string token;

  while(ss >> token) {
    if(is_operator(token)) { // token is an operator
      if(Stack.is_empty()) { // no numbers to operate on
        std::cout << "Not enough operands." << std::endl;
        break;
      } 
      double num2 = Stack.pop(); // at least one number to operate on
      if(token != "~") { // not a unary operation, need 2 numbers
        if(Stack.is_empty()) { 
          std::cout << "Not enough operands." << std::endl;   
        }
        double num1 = Stack.pop(); // normal operation
        double result = operation(token, num1, num2);
        Stack.push(result);
      } else { // unary operator
        double result = operation(token, num2, 0);
        Stack.push(result);
      }
      
    } else { // not an operator
      return 0;
    }
  }
}
