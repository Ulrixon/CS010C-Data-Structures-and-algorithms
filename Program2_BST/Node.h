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
    string data;
    int count = 0;
    Node(const string& val);
    ~Node();
    Node(const Node &) = delete;            // prohibit copy
    Node &operator=(const Node &) = delete; // prohibit copy assignment
};




#endif