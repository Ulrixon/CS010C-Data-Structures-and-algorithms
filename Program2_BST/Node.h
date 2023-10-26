#include <string>
#ifndef NODE_H
#define NODE_H
using namespace std;
class Node
{
private:
    Node *LeftPointer;
    Node *RightPointer;
    string data;
    int count = 0;

public:
    Node(string val);
    ~Node();
    
};

Node::Node(/* args */)
{
}

Node::~Node()
{
}


#endif