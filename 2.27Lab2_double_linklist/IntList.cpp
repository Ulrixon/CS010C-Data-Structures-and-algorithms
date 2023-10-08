#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList()
{
    IntNode *dummyNodeHead = new IntNode(0);
    IntNode *dummyNodeTail = new IntNode(0);
    this->dummyHead = dummyNodeHead;
    this->dummyTail = dummyNodeTail;
    // this->dummyHead->prev = NULL;
    this->dummyHead->next = dummyTail;
    this->dummyTail->prev = dummyHead;
    // this->dummyTail->next = NULL;
}

IntList::~IntList()
{
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
    if (!(this->dummyHead->next == this->dummyTail))
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
    if (!(this->dummyTail->prev == this->dummyHead))
    {
        this->dummyTail->prev = this->dummyTail->prev->prev;
        this->dummyTail->prev->next = this->dummyTail;
    }
}

bool IntList::empty() const
{
    int count = 0;
    IntNode *currNode = this->dummyHead;
    while (currNode != 0)
    {
        count++;
        currNode = currNode->next;
    }
    if (count == 2)
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
    if (currNode != rhs.dummyTail)
    {
        out << currNode->data;
        currNode = currNode->next;
    }

    while (currNode != rhs.dummyTail)
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
    if (currNode != this->dummyHead)
    {
        cout << currNode->data;
        currNode = currNode->prev;
    }
    while (currNode != this->dummyHead)
    {
        cout << " " << currNode->data;
        currNode = currNode->prev;
    }
}