#include "Stack.h"

class Node {
public:
    double data;
    Node* next;

    Node(double n) {
        this->data = n;
        this->next = nullptr;
    }
};
