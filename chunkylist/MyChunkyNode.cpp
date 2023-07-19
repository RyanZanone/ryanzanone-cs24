#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode()
{
    chunk = new std::string;
    prev_ref = nullptr;
    next_ref = nullptr;
}