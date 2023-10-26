#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList()
{
    IntNode *dummyNodeHead = new IntNode(0);
    IntNode *dummyNodeTail = new IntNode(0);
    this->dummyHead = dummyNodeHead; // point the dummyhead and tail to new nodes
    this->dummyTail = dummyNodeTail;

    this->dummyHead->next = dummyTail; // connect new nodes
    this->dummyTail->prev = dummyHead;
}

IntList::~IntList() // delete Node start from dummyHead to the end
{
    IntNode *currNode = dummyHead;
    IntNode *prevNode = dummyHead;
    while (currNode->next != 0)
    {
        prevNode = currNode;
        currNode = currNode->next;
        delete prevNode;
    }
    delete currNode;
}

void IntList::push_front(int value)
{
    IntNode *currNode = new IntNode(value);
    currNode->next = this->dummyHead->next;
    currNode->prev = this->dummyHead;
    this->dummyHead->next->prev = currNode;
    this->dummyHead->next = currNode;
}

void IntList::pop_front()
{
    if (!(this->dummyHead->next == this->dummyTail)) // if this list is not empty (means only dummy nodes exists)
    {
        this->dummyHead->next = this->dummyHead->next->next;
        this->dummyHead->next->prev = this->dummyHead;
    }
}

void IntList::push_back(int value)
{
    IntNode *currNode = new IntNode(value);
    currNode->next = this->dummyTail;
    currNode->prev = this->dummyTail->prev;
    this->dummyTail->prev->next = currNode;
    this->dummyTail->prev = currNode;
}

void IntList::pop_back()
{
    if (!(this->dummyTail->prev == this->dummyHead)) // if this list is not empty (means only dummy nodes exists)
    {
        this->dummyTail->prev = this->dummyTail->prev->prev;
        this->dummyTail->prev->next = this->dummyTail;
    }
}

bool IntList::empty() const
{
    int count = 0;
    IntNode *currNode = this->dummyHead;
    while (currNode != 0) // compute how many node in total
    {
        count++;
        currNode = currNode->next;
    }
    if (count == 2) // if only dummy nodes exists
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream &operator<<(std::ostream &out, const IntList &rhs)
{
    IntNode *currNode = rhs.dummyHead->next;
    if (currNode != rhs.dummyTail) // if currNode is not dummyTail print data and go to next node
    {
        out << currNode->data;
        currNode = currNode->next;
    }

    while (currNode != rhs.dummyTail) // while currNode is not dummyTail print data and go to next node
    {

        out << " " << currNode->data;
        currNode = currNode->next;
    }
    out << "";
    return out;
}

void IntList::printReverse() const
{
    IntNode *currNode = this->dummyTail->prev;
    if (currNode != this->dummyHead) // if currNode is not dummyHead print data and go to prev node
    {
        cout << currNode->data;
        currNode = currNode->prev;
    }
    while (currNode != this->dummyHead) // while currNode is not dummyHead print data and go to prev node
    {
        cout << " " << currNode->data;
        currNode = currNode->prev;
    }
}