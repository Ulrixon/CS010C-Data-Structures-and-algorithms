#include <string>
#ifndef NODE_H
#define NODE_H
using namespace std;
class Node
{
private:
    

public:
    Node *LeftPointer;
    Node *RightPointer;
    Node *Parent;
    string data;
    Node(const string& val);
    ~Node();
    Node(const Node &) = delete;            // prohibit copy
    Node &operator=(const Node &) = delete; // prohibit copy assignment
};
#endif