#include "MyGrove.h"

MyGrove::MyGrove(const char* str) {
    if(str) {
        root = new Node(str, strlen(str));     
    }
    else {
        root = nullptr;
    }
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
    if (!node) {
        throw std::out_of_range("Node is null");
    }

    if (index < 0 || index >= node->length) {
        throw std::out_of_range("Invalid index");
    }

    if (!node->left && !node->right) {
        if (!node->str) {
            throw std::runtime_error("String is null");
        }
        return node->str[index];
    }

    if (index < node->left->length) {
        return findChar(node->left, index);
    } else {
        return findChar(node->right, index - node->left->length);
    }
}

const MyGrove* MyGrove::substr(int i, int j) const {
    if (!root || i < 0 || j < i || j > root->length) {
        throw std::out_of_range("Invalid indices");
    }

    if (i == 0 && j == root->length) {
        // If the substring covers the entire string, return a copy of this.
        return this;
    }

    // Create a helper function to perform the substring operation recursively.
    auto substringHelper = [](Node* node, int start, int end) -> Node* {
        if (!node) {
            return nullptr;
        }

        if (start == 0 && end >= node->length) {
            // If the substring fully covers this node, return a copy of the entire node.
            return new Node(node->str, node->length);
        }

        if (end <= 0) {
            // If the substring is entirely to the left of this node, return nullptr.
            return nullptr;
        }

        // The substring overlaps with this node.
        int leftStart = std::max(0, start);
        int leftEnd = std::min(node->left->length, end);

        int rightStart = std::max(0, start - node->left->length);
        int rightEnd = std::min(end - node->left->length, node->length);

        Node* leftSubstr = nullptr;
        Node* rightSubstr = nullptr;

        if (leftStart < leftEnd) {
            leftSubstr = substringHelper(node->left, leftStart, leftEnd);
        }

        if (rightStart < rightEnd) {
            rightSubstr = substringHelper(node->right, rightStart, rightEnd);
        }

        if (!leftSubstr && !rightSubstr) {
            return nullptr;
        }

        int newLength = end - start;
        Node* newRoot = new Node(nullptr, newLength);
        newRoot->left = leftSubstr;
        newRoot->right = rightSubstr;

        return newRoot;
    };

    Node* newRoot = substringHelper(root, i, j);
    MyGrove* substring = new MyGrove(nullptr);
    substring->root = newRoot;

    return substring;
}

MyGrove::Node* MyGrove::substringHelper(Node* node, int start, int end) const {
    if (!node) {
        return nullptr;
    }

    if (start == 0 && end >= node->length) {
        // If the substring fully covers this node, return a copy of the entire node.
        return new Node(node->str, node->length);
    }

    if (end <= 0) {
        // If the substring is entirely to the left of this node, return nullptr.
        return nullptr;
    }

    if (start >= node->length) {
        // If the substring is entirely to the right of this node, continue searching in the right child.
        return substringHelper(node->right, start - node->length, end - node->length);
    }

    // The substring overlaps with this node.
    int leftStart = std::max(0, start);
    int leftEnd = std::min(start + node->left->length, end);

    int rightStart = std::max(0, start - node->left->length);
    int rightEnd = std::min(end - node->left->length, node->length);

    Node* leftSubstr = substringHelper(node->left, leftStart, leftEnd);
    Node* rightSubstr = substringHelper(node->right, rightStart, rightEnd);

    int newLength = end - start;
    Node* newRoot = new Node(nullptr, newLength);
    newRoot->left = leftSubstr;
    newRoot->right = rightSubstr;

    return newRoot;
}



