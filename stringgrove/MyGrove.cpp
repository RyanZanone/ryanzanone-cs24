#include "MyGrove.h"

MyGrove::MyGrove(const char* str) {
    root = new Node(str, strlen(str));
}

int MyGrove::len() const {
    return root->length;
}

const MyGrove* MyGrove::concat(MyGrove* other) const {
    if(!root) {
        return other;
    }

    if(!other->root) {
        return this;
    }

    Node* newRoot = new Node(nullptr, len() + other->len());
    newRoot->left = root;
    newRoot->right = other->root;
    newRoot->length = newRoot->left->length + newRoot->right->length;

    MyGrove* concatenated  = new MyGrove(nullptr);
    concatenated->root = newRoot;

    return concatenated;
}

char MyGrove::charAt(int index) const {
    if(!root || index < 0 || index >= root->length) {
        throw std::out_of_range("Index out of bounds");
    }

    return findChar(root, index);
}

char MyGrove::findChar(Node* node, int index) const {
    if(!node->left && !node->right) {
      return node->str[index];
    }

    if(index < node->left->length) {
      return findChar(node->left, index);
    }
    else {
      return findChar(node->right, index - node->left->length);
    }
}

const MyGrove* MyGrove::substr(int start, int end) const {
    if (!root || start < 0 || end > root->length || start > end)
        throw std::out_of_range("Invalid substring indices");

    int length = end - start;
    if (length == 0)
        return new MyGrove(nullptr);

    Node* newRoot = new Node(nullptr, length);
    newRoot->left = findSubstring(root, start, start + length);
    newRoot->length = length;

    MyGrove* substring = new MyGrove(nullptr);
    substring->root = newRoot;

    return substring;
}

MyGrove::Node* MyGrove::findSubstring(Node* node, int start, int end) const {
    if (!node) {
        return nullptr;
    }

    int nodeStart = 0;
    int nodeEnd = node->length;

    if (start == 0 && end == nodeEnd) {
        // The requested substring covers the entire node
        return node;
    }

    if (end <= nodeStart || start >= nodeEnd) {
        // The requested substring is not within this node
        return nullptr;
    }

    if (start <= nodeStart && end >= nodeEnd) {
        // The entire node is within the requested substring
        return node;
    }

    // Calculate the new start and end positions for the children
    int leftStart = start;
    int leftEnd = std::min(end, node->left->length);
    int rightStart = std::max(start - node->left->length, 0);
    int rightEnd = end - node->left->length;

    Node* left = findSubstring(node->left, leftStart, leftEnd);
    Node* right = findSubstring(node->right, rightStart, rightEnd);

    if (!left && !right) {
        return nullptr;
    }

    if (!left) {
        return right;
    }

    if (!right) {
        return left;
    }

    // Create a new node to represent the combined substring
    Node* newRoot = new Node(nullptr, end - start);
    newRoot->left = left;
    newRoot->right = right;
    newRoot->length = end - start;

    return newRoot;
}


