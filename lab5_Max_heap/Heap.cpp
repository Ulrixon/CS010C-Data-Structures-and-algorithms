#include "PrintJob.h"
#include "Heap.h"
#include <iostream>
#include <math.h>
Heap::Heap()
{
}

Heap::~Heap() // we need to first delete all pointer in the array then we can delete it
{
}
void swapPrintJob(PrintJob *&joba, PrintJob *&jobb) // swap pointers
{
    PrintJob *tmpJob = joba;
    joba = jobb;
    jobb = tmpJob;
}

void Heap::enqueue(PrintJob *job)
{
    if (numItems == MAX_HEAP_SIZE) // array is full
    {
        cout << "array overflow";
        return;
    }
    arr[numItems] = job;
    numItems++;
    int currentIndex = numItems - 1;
    while (true) // keep swapping with parent if priority is higher
    {
        if (arr[(currentIndex - 1) / 2]->getPriority() < arr[currentIndex]->getPriority())
        {
            swapPrintJob(arr[(currentIndex - 1) / 2], arr[currentIndex]);
            currentIndex = floor((currentIndex - 1) / 2);
        }
        else // no need to swap so break the loop
        {
            break;
        }
    }
}

void Heap::trickleDown(int currentIndex)
{
    while (true) // keep swap with child which has higher priority until no child can swap
    {
        if ((2 * currentIndex + 1) <= (numItems - 1)) // check if left child is exists
        {
            if (arr[currentIndex]->getPriority() < arr[2 * currentIndex + 1]->getPriority()) // priority smaller than left child
            {
                if ((2 * currentIndex + 2) <= (numItems - 1)) // if right child exists
                {
                    if (arr[2 * currentIndex + 1]->getPriority() < arr[2 * currentIndex + 2]->getPriority()) // if right child bigger than left child
                    {
                        swapPrintJob(arr[currentIndex], arr[2 * currentIndex + 2]);
                        currentIndex = 2 * currentIndex + 2;
                    }
                    else // if right not bigger than left
                    {
                        swapPrintJob(arr[currentIndex], arr[2 * currentIndex + 1]);
                        currentIndex = 2 * currentIndex + 1;
                    }
                }
                else // if right child not exists just swap left
                {
                    swapPrintJob(arr[currentIndex], arr[2 * currentIndex + 1]);
                    currentIndex = 2 * currentIndex + 1;
                }
            }
            else
            {
                if ((2 * currentIndex + 2) <= (numItems - 1)) // check if right child exists
                {
                    if (arr[currentIndex]->getPriority() < arr[2 * currentIndex + 2]->getPriority())
                    {
                        swapPrintJob(arr[currentIndex], arr[2 * currentIndex + 2]); // because if left is bigger than right, they will already swap in first if in while loop
                        currentIndex = 2 * currentIndex + 2;
                    }
                    else
                    {
                        return; // no child can swap
                    }
                }
                else
                {
                    return; // no child can swap
                }
            }
        }
        else
        {
            return; // no child to swap
        }
    }
}

void Heap::dequeue()
{
    if (numItems == 0) // array is empty
    {
        cout << "array underflow";
        return;
    }
    delete arr[0];
    arr[0] = arr[numItems - 1];
    int currentIndex = 0;
    trickleDown(currentIndex);
    numItems--;
}

PrintJob *Heap::highest()
{
    if (numItems == 0) // array is empty
    {
        cout << "array underflow";
        return NULL;
    }
    return arr[0];
}

void Heap::print()
{
    PrintJob *high = highest();
    cout << "Priority: " << high->getPriority() << ", Job Number: " << high->getJobNumber() << ", Number of Pages: " << high->getPages() << endl;
}
