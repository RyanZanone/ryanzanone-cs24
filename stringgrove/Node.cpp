#include <string>

class Node {
private:
    std::string *data;
    Node *left_child;
    Node *right_child;

public:
    Node(std::string *data) { // Constructor
        this->data = data;
        left_child = nullptr;
        right_child = nullptr;
    }

    bool is_leaf() {
        return (left_child == nullptr && right_child == nullptr);
    }

    
};