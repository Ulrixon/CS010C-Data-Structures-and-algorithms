#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList()
{

    this->dummyHead = dummyNodeHead;
    this->dummyTail = dummyNodeTail;
    dummyHead->prev = nullptr;
    dummyHead->next = dummyNodeTail;
    dummyTail->prev = dummyNodeHead;
    dummyTail->next = nullptr;
}

IntList::~IntList()
{
    delete this;
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
    if (!this->dummyTail->prev->data == 0)
    {
        this->dummyTail->prev = this->dummyTail->prev->prev;
        this->dummyTail->prev->next = this->dummyTail;
    }
}

bool IntList::empty() const
{
    int count = 0;
    IntNode *currNode = dummyHead;
    while (currNode != nullptr)
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