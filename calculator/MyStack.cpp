#include "MyStack.h"

MyStack::MyStack() {
    topnode = nullptr;
}

MyStack::~MyStack() {
    while(!is_empty()) {
        pop();
    }
}

void MyStack::clear() {
    while(!is_empty()) {
        Node* tempnode = topnode;
        topnode = topnode->next;
        delete tempnode;
    }
    count = 0;
}

bool MyStack::is_empty() const {
    return topnode == nullptr;
}

void MyStack::push(double item) {
    Node* newnode = new Node(item);
    newnode->next = topnode;
    topnode = newnode;
    count += 1;
}

double MyStack::pop() {
    if(is_empty()) { // stack is empty
        throw std::underflow_error("Stack is Empty");
    } else {
        double topdata = topnode->data;
        Node* tempnode = topnode;
        topnode = topnode->next;
        delete tempnode;
        count -= 1;
        return topdata;
    }
}

double MyStack::top() const {
    if(is_empty()) {
        throw std::underflow_error("Stack is Empty");
    } else {
        return topnode->data;
    }
}

int MyStack::size() const {
    return count;
}