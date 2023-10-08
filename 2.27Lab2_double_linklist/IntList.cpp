#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList()
{
    IntNode *dummyNodeHead = new IntNode(0);
    IntNode *dummyNodeTail = new IntNode(0);
    this->dummyHead = dummyNodeHead;
    this->dummyTail = dummyNodeTail;
    dummyHead->prev = nullptr;
    dummyNodeHead->next = dummyNodeTail;
    dummyNodeTail->prev = dummyNodeHead;
    dummyNodeTail->next = nullptr;
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
    if (!this->dummyHead->next->data == 0)
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
}