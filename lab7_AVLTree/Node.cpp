#include "Node.h"

Node::Node(const string &val) {
  data = val;
  this->Parent = NULL;
  this->LeftPointer = NULL;
  this->RightPointer = NULL;
}

Node::~Node() {}