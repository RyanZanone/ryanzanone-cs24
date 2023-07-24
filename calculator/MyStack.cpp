#include "MyStack.h"

MyStack::MyStack() {
    head = nullptr;
    tail = nullptr;
}

MyStack::~MyStack() {
    Node* currnode = head;
    while(currnode != nullptr) {
        Node* next = head->next;
        delete currnode;
        currnode = next;
    }
}

void MyStack::clear() {
    Node* currnode = head;
    while(currnode != nullptr) {
        Node* next = head->next;
        delete currnode;
        currnode = next;
    }
}

bool MyStack::is_empty() const {
    if(head == nullptr) { // stack is empty
        return true;
    }
    else {
        return false;
    }
}

void MyStack::push(double item) {
    if(head == nullptr) { // stack is empty
        Node* newnode = new Node(item);
        head = newnode;
        tail = newnode;
    }
    else {
        Node* newnode = new Node(item);
        tail->next = newnode;
        tail = newnode;
    }
}

double MyStack::pop() {
    if(head == nullptr) { // stack is empty
        throw std::underflow_error("Stack is Empty");
    } else {
        Node* currnode = head;
        while(currnode->next != tail) {
            currnode = currnode->next;
        }
        double top_data = tail->data;
        tail = currnode;
        return top_data;
    }
}

double MyStack::top() const {
    if(head == nullptr) { // stack is empty
        throw std::underflow_error("Stack is Empty");
    } else {
        return tail->data;
    }
}