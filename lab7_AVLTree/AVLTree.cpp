#include "AVLTree.h"
#include <cstddef>
#include <iostream>

AVLTree::AVLTree() { root = NULL; }

AVLTree::~AVLTree() {}

int height_of_key(Node *currNode) // find this subtree's max depth
{
  if (currNode == NULL) // these ifs are finding the Node to be searched
  {
    return -1;
  }
  if (currNode->LeftPointer != NULL && currNode->RightPointer != NULL) {
    return 1 + max(height_of_key(currNode->LeftPointer),
                   height_of_key(currNode->RightPointer));
  } else if (currNode->LeftPointer != NULL) {
    return 1 + height_of_key(currNode->LeftPointer);
  } else if (currNode->RightPointer != NULL) {
    return 1 + height_of_key(currNode->RightPointer);
  }

  return 0;
}

Node *AVLTree::findUbalancedNode(Node *node) {
  
  if (abs(balanceFactor(node)) == 2) { // if it is unbalance
    return node;
  } // else keep finding if its parent is unblance
  if (node->Parent == NULL) {
    return NULL;
  } else {
    return findUbalancedNode(node->Parent);
  }
}

void AVLTree::rotateLeft(Node *node) {
  Node *RightLeftChild = node->RightPointer->LeftPointer;
  Node *RightChild = node->RightPointer;
  RightChild->Parent = node->Parent;
  if (node->Parent == NULL) {
    root = RightChild;
  } else if (node->Parent->LeftPointer ==
             node) { // check node if node is Parent's left child or right child
                     // and make right child become parent's child
    node->Parent->LeftPointer = RightChild;
  } else {
    node->Parent->RightPointer = RightChild;
  }

  RightChild->LeftPointer = node; // assign node to be right child's left child
  node->RightPointer = RightLeftChild; // let node's right child's left child
                                       // become node's right child
  if (RightLeftChild!=NULL) {
    RightLeftChild->Parent = node;
  }
  node->Parent = RightChild;
}

void AVLTree::rotateRight(Node *node) {
  Node *LeftRightChild = node->LeftPointer->RightPointer;
  Node *LeftChild = node->LeftPointer;
  LeftChild->Parent = node->Parent;
  if (node->Parent == NULL) {
    root = LeftChild;
  } else if (node->Parent->LeftPointer ==
             node) { // check node if node is Parent's left child or right child
                     // and make right child become parent's child
    node->Parent->LeftPointer = LeftChild;
  } else {
    node->Parent->RightPointer = LeftChild;
  }

  LeftChild->RightPointer = node; // assign node to be Left child's right child
  node->LeftPointer = LeftRightChild; // let node's left child's right child
                                      // become node's left child
  if (LeftRightChild!=NULL) {
    LeftRightChild->Parent = node;
  }
  
  node->Parent = LeftChild;
}

int AVLTree::balanceFactor(
    Node *node) { // return balance factor, don't input null node
  return height_of_key(node->LeftPointer) - height_of_key(node->RightPointer);
}

void AVLTree::rotate(Node *node) { // rotate if unbalance, don't input leaf node
  if (node == NULL) {
    return;
  }
  if (balanceFactor(node) == 2) {  // if left subtree is much more nodes
    if (balanceFactor(node->LeftPointer) == -1) { // if subtree's right subtree is much more node need left rotate first
      rotateLeft(node->LeftPointer);
    }
    rotateRight(node);
  } else if (balanceFactor(node) == -2) {
    if (balanceFactor(node->RightPointer) == 1) {
      rotateRight(node->RightPointer);
    }
    rotateLeft(node);
  }
}

void AVLTree::insert(const string &newString) {
  if (root == NULL) {

    root = new Node(newString); // no need to balance a tree only have one node
  } else {
    Node *currNode = root;
    Node *unbalanceNode = NULL;

    while (currNode != NULL) // while it is not leaf keep going down
    {
      if (currNode->data > newString) {
        if (currNode->LeftPointer == NULL) {
          currNode->LeftPointer = new Node(newString);
          currNode->LeftPointer->Parent = currNode;
          unbalanceNode = findUbalancedNode(currNode);
          rotate(unbalanceNode);
          return;
        }

        currNode = currNode->LeftPointer;
      } else if (currNode->data < newString) {
        if (currNode->RightPointer == NULL) {
          currNode->RightPointer = new Node(newString);
          currNode->RightPointer->Parent = currNode;
          unbalanceNode = findUbalancedNode(currNode);
          rotate(unbalanceNode);
          return;
        }

        currNode = currNode->RightPointer;
      } else // found duplicate Node
      {
        // currNode->count++; // duplicate string +1
        return;
      }
    }
  }
}

void AVLTree::printBalanceFactors(Node *node) {
  if (node == NULL)
    {
        return;
    }
    printBalanceFactors(node->LeftPointer);
    std::cout << node->data << "(" << balanceFactor(node) << "), ";
    printBalanceFactors(node->RightPointer);
}


void AVLTree::printBalanceFactors() { printBalanceFactors(root); }


void AVLTree::visualizeTree(const string &outputFilename){
    
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    
}