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
    if(num2 == 0) {
      return -1;
    }
    return num1 / num2;
  }
  if(op == "%") {
    if(num2= 0) {
      return -1;
    }
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
  MyStack Stack;

  while(std::getline(std::cin, input)) {
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
          if(result == -1) {
            std::cout << "Division by zero." << std::endl;
          } else {
            Stack.push(result);
          }
        } else { // unary operator
          double result = operation(token, num2, 0);
          Stack.push(result);
        }
        
      } else { // not an operator
        double num;
        try {
          num = std::stod(token);
        } catch (const std::exception&) {
          std::cout << "Unknown token." << std::endl;
        }
        Stack.push(num);
      }
    }

    if(Stack.is_empty()) {
      std::cout << "No expression." << std::endl;
    } else if(Stack.size() == 1) {
      double result = Stack.pop();
      std::cout << "= " << result << std::endl;
    } else {
      std::cout << "Too many operands" << std::endl;
      Stack.clear();
    }
  }

  return 0;
}

