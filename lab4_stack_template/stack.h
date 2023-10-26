#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class stack
{
private:
    static const int MAX_SIZE = 20;
    T data[MAX_SIZE];
    int size = 0;

public:
    stack();
    ~stack();
    stack(const stack &) = delete;            // prohibit copy
    stack &operator=(const stack &) = delete; // prohibit copy assignment
    void push(T val);
    void pop();
    void pop_two();
    T top();
    bool empty();
};
#endif

template<typename T>
stack<T>::stack()
{
}

template<typename T>
stack<T>::~stack()
{
}

template<typename T>
void stack<T>::push(T val)
{ //push value to the position of size and +1
    if(size == MAX_SIZE)
    {
        throw overflow_error("Called push on full stack.");
    }
    data[size] = val;
    size++;
}

template<typename T>
void stack<T>::pop()
{
    if(size != 0)
    {
        size--;
    }
    else
    {
        throw out_of_range("Called pop on empty stack.");
    }
}

template<typename T>
void stack<T>::pop_two()
{
    if(size == 0)
    {
        throw out_of_range("Called pop_two on empty stack.");
    }
    else if (size == 1)
    {
        throw out_of_range("Called pop_two on a stack of size 1.");
    }
    else
    {
        size--;
        size--;
    }
}

template<typename T>
T stack<T>::top()
{
    if(size == 0)
    {
        throw underflow_error("Called top on empty stack.");
    }
    else
    {
        return data[size - 1];
    }
}

template<typename T>
bool stack<T>::empty()
{
    if(size == 0)
    {
        return true;
    }
    return false;
}