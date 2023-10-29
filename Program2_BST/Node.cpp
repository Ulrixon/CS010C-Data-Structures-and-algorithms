#include "Node.h"

Node::Node(const string& val)
{
    data = val;
    this->LeftPointer = NULL;
    this->RightPointer = NULL;
}

Node::~Node()
{
}