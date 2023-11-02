#include "BSTree.h"
#include "Node.h"
#include <iostream>
using std::cout;

BSTree::BSTree()
{
    root = NULL;
}


void deleteAllNodeInBST(Node * currNode) // using recursive function to delete all node starting from leafs.
{
    if(currNode == NULL)
    {
        return;
    }

    deleteAllNodeInBST(currNode->LeftPointer);
    deleteAllNodeInBST(currNode->RightPointer);
    delete currNode;
}

BSTree::~BSTree()
{
    Node *currNode = root;
    if(root != NULL)
    {
        deleteAllNodeInBST(currNode);
    }
}



void BSTree::insert(const string &newString)
{

    if (root == NULL)
    {

        root = new Node(newString);
    }
    else
    {
        Node *currNode = root;

        while (currNode != NULL) // while it is not leaf keep going down
        {
            if (currNode->data > newString)
            {
                if (currNode->LeftPointer == NULL)
                {
                    currNode->LeftPointer = new Node(newString);
                    return;
                }

                currNode = currNode->LeftPointer;
            }
            else if (currNode->data < newString)
            {
                if (currNode->RightPointer == NULL)
                {
                    currNode->RightPointer = new Node(newString);
                    return;
                }

                currNode = currNode->RightPointer;
            }
            else // found duplicate Node
            {
                currNode->count++; // duplicate string +1
                return;
            }
        }
    }
}

void BSTree::remove_key(Node *currNode, Node *parentNode, const string &key)
{
    Node *tmpNode = NULL; // this pointer is to point the node going to be deleted
    if (currNode == NULL) // these outer ifs are finding the Node to be delete and it's parentNode
    {
        return;
    }
    else if (currNode->data > key)
    {
        parentNode = currNode;
        remove_key(currNode->LeftPointer, currNode, key);
    }
    else if (currNode->data < key)
    {
        parentNode = currNode;
        remove_key(currNode->RightPointer, currNode, key);
    }
    else // Node found
    {
        if (currNode->count > 0) // if count >0 then just minus 1 and stop this function because count start from 0
        {
            currNode->count--;
            return;
        }
        if (currNode->LeftPointer != NULL ) // two children or only left node
        {
            Node *successorNode = NULL;
            Node *parentSuccessorNode = NULL;
            successorNode = currNode->LeftPointer; // we are going to move left once and go right to the end
            parentSuccessorNode = currNode;
            while (successorNode->RightPointer != NULL)
            {
                parentSuccessorNode = successorNode;

                successorNode = successorNode->RightPointer;
            }
            currNode->data = successorNode->data;
            currNode->count = successorNode->count;
            for (int i = 0; i < (currNode->count + 1); i++) // delete succesor original node
            {
                remove_key(successorNode, parentSuccessorNode, successorNode->data);
            }
        }
        else if (currNode->RightPointer != NULL ) // only right node
        {
            Node *successorNode = NULL;
            Node *parentSuccessorNode = NULL;
            successorNode = currNode->RightPointer; // we are going to move right once and go left to the end
            parentSuccessorNode = currNode;
            while (successorNode->LeftPointer != NULL)
            {
                parentSuccessorNode = successorNode;

                successorNode = successorNode->LeftPointer;
            }
            currNode->data = successorNode->data;
            currNode->count = successorNode->count;
            for (int i = 0; i < (currNode->count + 1); i++) // delete succesor original node
            {
                remove_key(successorNode, parentSuccessorNode, successorNode->data);
            }
        }
        else if (root == currNode) // if currNode is root
        {
            root = NULL;
            delete currNode;
        }
        else // leaf
        {
            tmpNode = currNode;
            if (parentNode->LeftPointer == currNode)
            {
                if (currNode->LeftPointer != NULL)
                {
                    parentNode->LeftPointer = currNode->LeftPointer;
                }
                else
                {
                    parentNode->LeftPointer = currNode->RightPointer;
                }
            }
            else
            {
                if (currNode->LeftPointer != NULL)
                {
                    parentNode->RightPointer = currNode->LeftPointer;
                }
                else
                {
                    parentNode->RightPointer = currNode->RightPointer;
                }
            }
            delete tmpNode;
            
        }
        
        
    }
}

void BSTree::remove(const string &key)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        remove_key(root, NULL, key); //call recursive function
    }
}
bool search_key(Node *currNode, const string &key)
{
    if (currNode == NULL) // these ifs are finding the Node to be searched
    {
        return false;
    }
    else if (currNode->data > key)
    {

        return search_key(currNode->LeftPointer, key);
    }
    else if (currNode->data < key)
    {
        return search_key(currNode->RightPointer, key);
    }
    else // Node found
    {
        return true;
    }
    return false;
}

bool BSTree::search(const string &key) const
{
    return search_key(root, key); // call recursive funtion
}

string BSTree::largest() const
{                     // find the rightest one
    if (root == NULL) // if empty
    {
        return "";
    }
    else
    {
        Node *currNode = root;
        while (currNode->RightPointer != NULL) // go to the right side of Node
        {
            currNode = currNode->RightPointer;
        }
        return currNode->data;
    }
}

string BSTree::smallest() const // find the leftest one
{
    if (root == NULL) // if empty
    {
        return "";
    }
    else
    {
        Node *currNode = root;
        while (currNode->LeftPointer != NULL) // go to the left side of Node
        {
            currNode = currNode->LeftPointer;
        }
        return currNode->data;
    }
}

int height_of_key(Node *currNode, const string &key) // find this subtree's max depth
{
    if (currNode == NULL) // these ifs are finding the Node to be searched
    {
        return 0;
    }
    if (currNode->LeftPointer != NULL && currNode->RightPointer != NULL)
    {
        return 1+max(height_of_key(currNode->LeftPointer, key),height_of_key(currNode->RightPointer, key));
    }
    else if (currNode->LeftPointer != NULL)
    {
        return 1+height_of_key(currNode->LeftPointer, key);
    }
    else if (currNode->RightPointer != NULL)
    {
        return 1+height_of_key(currNode->RightPointer, key);
    }
    
    return 0;
}



int BSTree::height(const string &key) const
{
    Node *currNode = root;
    while (currNode != NULL) // find the key's location
    {
        if (currNode->data > key)
        {
            currNode = currNode->LeftPointer;
        }
        else if (currNode->data < key)
        {
            currNode = currNode->RightPointer;
        }
        else
        {
            break;
        }
    }
    
    

    if (!search_key(root, key)) // if tree is empty or Node not found
    {
        return -1;
    }
    else // caculate tree height
    {
        return height_of_key(currNode, key);
    }
}

void BSTPrintPreorder(Node *currNode) // node left right
{
    if (currNode == NULL)
    {
        return;
    }
    std::cout << currNode->data << "(" << (currNode->count + 1) << "), ";
    BSTPrintPreorder(currNode->LeftPointer);
    BSTPrintPreorder(currNode->RightPointer);
}

void BSTree::preOrder() const
{
    BSTPrintPreorder(root); // call recursive fuction
}

void BSTPrintPostorder(Node *currNode) // left right node
{
    if (currNode == NULL)
    {
        return;
    }

    BSTPrintPostorder(currNode->LeftPointer);
    BSTPrintPostorder(currNode->RightPointer);
    std::cout << currNode->data << "(" << (currNode->count + 1) << "), ";
}

void BSTree::postOrder() const
{
    BSTPrintPostorder(root); // call recursive fuction
}

void BSTPrintInorder(Node *currNode) // left node right
{
    if (currNode == NULL)
    {
        return;
    }
    BSTPrintInorder(currNode->LeftPointer);
    std::cout << currNode->data << "(" << (currNode->count + 1) << "), ";
    BSTPrintInorder(currNode->RightPointer);
}

void BSTree::inOrder() const
{
    BSTPrintInorder(root); // call recursive fuction
}