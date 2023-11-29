#include "Node.h"
#include <cstddef>
#include <string>

Node::Node(const string &key) {
  small = key;
  large = "";
  left = NULL;
  middle = NULL;
  right = NULL;
  parent = NULL;
}

Node::~Node() {}
