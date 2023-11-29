#include "Tree.h"
#include "Node.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
Tree::Tree() { root = NULL; }

void Tree::recursiveRemove(Node *currNode) {
  if (currNode == NULL) {
    return;
  }
  recursiveRemove(currNode->left);
  recursiveRemove(currNode->middle);
  recursiveRemove(currNode->right);
  delete currNode;
}
// delete all node recursively
Tree::~Tree() {recursiveRemove(root);}

bool Tree::isFull(Node *node) const{
  if (node == NULL) {
    return false;
  } else if (node->large == "") {
    return false;
  }
  return true;
}

Node *Tree::split(Node *node, const string &key) { // split full node
  Node *parentNode = NULL;
  if (key <= node->small) { // this mean key is push from left node
    if (isFull(node->parent)) {
      parentNode = split(node->parent, node->small);
    } else {
      parentNode = insertUpward(node->parent, node->small);
    }
    if (parentNode->small >=
        key) { // only one key in parent node or double key but push from left
      parentNode->left =
          new Node(key); // connect parent node with new seperated node
      parentNode->left->parent = parentNode;
      parentNode->middle = node;
      node->parent = parentNode;
      node->small = node->large;
      node->large = "";
      return parentNode->left;
    } else {
      if (parentNode->large.compare("") ==
          0) { // middle child and split parent case
       throw runtime_error("not done yet"); 
      } else {
        parentNode->middle =
            new Node(key); // connect parent node with new seperated node
        parentNode->middle->parent = parentNode;
        parentNode->right = node;
        node->parent = parentNode;
        node->small = node->large;
        node->large = "";
        return parentNode->middle;
      }
    }
  } else if (key > node->small &&
             key <= node->large) { // key pushed from middle
    if (isFull(node->parent)) {
      parentNode = split(node->parent, key);
    } else {
      parentNode = insertUpward(node->parent, key);
    }

    if (parentNode->small >=
        key) { // only one key in parent node or double key but push from left
      parentNode->left =
          new Node(node->small); // connect parent node with new seperated node
      parentNode->left->parent = parentNode;
      parentNode->middle = node;
      node->parent = parentNode;
      node->small = node->large;
      node->large = "";
      node->left = node->middle; // assign original node's middle and right
                                 // subtree to new middle node
      node->middle = node->right;
      return parentNode->left;
    } else {
      if (parentNode->large.compare("") ==
          0) { // middle child and split parent case
        throw runtime_error("not done yet");
      } else {

        parentNode->middle = new Node(
            node->small); // connect parent node with new seperated node
        parentNode->middle->parent = parentNode;
        parentNode->right = node;
        node->parent = parentNode;
        node->small = node->large;
        node->large = "";
        node->left = node->middle; // assign original node's middle and right
                                   // subtree to new middle node
        node->middle = node->right;
        return parentNode->middle;
      }
    }
  } else { // key is the rightest one
    if (isFull(node->parent)) {
      parentNode = split(node->parent, node->large);
    } else {
      parentNode = insertUpward(node->parent, node->large);
    }
    if (parentNode->small >=
        key) { // only one key in parent node or double key but push from left
      parentNode->left = node;
      // connect parent node with new seperated node

      parentNode->middle = new Node(key);
      node->parent = parentNode;
      parentNode->middle->parent = parentNode;
      node->large = "";
      return parentNode->middle;
    } else {
      if (parentNode->large.compare("") ==
          0) { // middle child and split parent case
        throw runtime_error("not done yet");
      } else {

        parentNode->middle =
            node; // connect parent node with new seperated node
        node->parent = parentNode;
        parentNode->right = new Node(key);
        parentNode->right->parent = parentNode;
        node->large = "";

        return parentNode->right;
      }
    }
  }
  return NULL;
}

Node *Tree::insertUpward(Node *node, const string &key) {
  if (node == NULL) { // no parent node
    //cout << "test" << endl;
    node = new Node(key);
    root = node;
    return node;
  } else { // one key parent node case
    if (node->small >= key) {
      node->large = node->small;
      node->small = key;
      node->right = node->middle;
      return node;
    } else {
      node->large = key;
      return node;
    }
  }
}


Node *Tree::findInsertPosition(const string &key) {
  if (root == NULL) {
    return root;
  } else {
    Node *currNode = root;
    while (true) {
      if (currNode->small >= key) {
        if (currNode->left != NULL) {
          currNode = currNode->left;
        } else { // end of tree
          return currNode;
        }
      } else if (currNode->small < key && currNode->large > key &&
                 isFull(currNode)) {
        if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return currNode;
        }
      } else if (currNode->large < key && isFull(currNode)) {
        if (currNode->right != NULL) {
          currNode = currNode->right;
        } else { // end of tree
          return currNode;
        }
      } else { // only one string in node but key > string
        if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return currNode;
        }
      }
    }
  }
  return NULL;
}

void Tree::insert(const string &key) {
  Node *node = findInsertPosition(key);
  if (root == NULL) {
    root = new Node(key);
    return;
  }
  if (isFull(node)) {
    split(node, key);
  }
  else { // situation when leaf node is not full
    if (node->small >= key) {
      node->large = node->small;
      node->small = key;
      return;
    }
    else {
      node->large = key;
      return;
    }
  }
}

bool Tree::search(const string &key) const {
  if (root == NULL) {
    return root;
  } else {
    Node *currNode = root;
    while (true) {
      if (currNode->small > key) {
        if (currNode->left != NULL) {
          currNode = currNode->left;
        } else { // end of tree
          return false;
        }
      } else if (currNode->small < key && currNode->large > key &&
                 isFull(currNode)) {
        if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return false;
        }
      } else if (currNode->large < key && isFull(currNode)) {
        if (currNode->right != NULL) {
          currNode = currNode->right;
        } else { // end of tree
          return false;
        }
      } else if (! isFull(currNode)) 
      { // only one string in node but key > string
        if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return false;
        }
      }
      else { // node found
        return true;
      }
    }
  }
  return false;
}

void Tree::PrintInorder(Node *currNode) const// left node right
{
    if (currNode == NULL)
    {
        return;
    }
    PrintInorder(currNode->left);
    
    std::cout << currNode->small << ", ";

    PrintInorder(currNode->middle);
    if (currNode->large != "") {
      std::cout << currNode->large << ", ";
    }
    PrintInorder(currNode->right);
}

void Tree::inOrder() const
{
    PrintInorder(root); // call recursive fuction
}

void Tree::PrintPreorder(Node *currNode) const// left node right
{
    if (currNode == NULL)
    {
        return;
    }
    std::cout << currNode->small << ", ";

    PrintPreorder(currNode->left);
    if (currNode->large != "") {
        std::cout << currNode->large << ", ";
    }
    PrintPreorder(currNode->middle);
    
    PrintPreorder(currNode->right);
}

void Tree::preOrder() const
{
    PrintPreorder(root); // call recursive fuction
}

void Tree::PrintPostorder(Node *currNode) const// left node right
{
    if (currNode == NULL)
    {
        return;
    }
    PrintPostorder(currNode->left);
    PrintPostorder(currNode->middle);
    std::cout << currNode->small << ", ";
    PrintPostorder(currNode->right);
    
    if (currNode->large != "") {
      std::cout << currNode->large << ", ";
    }
}

void Tree::postOrder() const
{
    PrintPostorder(root); // call recursive fuction
}

Node *Tree::findRemovePosition(const string &key) {
  if (root == NULL) {
    return root;
  } else {
    Node *currNode = root;
    while (true) {
      if (currNode->small > key) {
        if (currNode->left != NULL) {
          currNode = currNode->left;
        } else { // end of tree
          return currNode;
        }
      } else if (currNode->small < key && currNode->large > key &&
                 isFull(currNode)) {
        if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return currNode;
        }
      } else if (currNode->large < key && isFull(currNode)) {
        if (currNode->right != NULL) {
          currNode = currNode->right;
        } else { // end of tree
          return currNode;
        }
      } else { // only one string in node but key > string
        if (currNode->small < key && !isFull(currNode)) {
          if (currNode->middle != NULL) {
          currNode = currNode->middle;
        } else { // end of tree
          return currNode;
        }
        }
        else { // key is in this node
          return currNode;
        }
        
      }
    }
  }
  return NULL;
}

void Tree::remove(const string &key) {
    Node *node = findRemovePosition(key);
    //cout << node->small << endl;
  if (node->small == key && !isFull(node)) { // only single key
    //cout << "test1" << endl;
    if (node->parent == NULL && node->left == NULL) { // if node is root node with no child
      root = NULL;
      delete node;
    }
    else {
      if (node->parent == NULL) { // delete root node case
        if (!isFull(node)) {
          Node *leftNode = node->left;
          Node *rightNode = node->middle;
          delete node;
          root = leftNode;
          leftNode->large = rightNode->small;
        }
      } else {
        Node * nodeParent =node->parent;
        if (node->parent->left == node) { // delete left child case
          node->parent->large = node->parent->middle->small;
          delete node->parent->middle;
          delete node;
          nodeParent->left = NULL;
          nodeParent->middle = NULL;
        }
        else if (node->parent->middle == node) { // delete right child case
          node->parent->large = node->parent->small;
          node->parent->small = node->parent->left->small;
          delete node->parent->left;
          delete node;
          nodeParent->left = NULL;
          nodeParent->middle = NULL;
        }
      }
    }
    
  }
  else if (node->small == key) { // if the node is full
    node->small = node->large;
    node->large = "";
  } else {
    //cout << "test2" << endl;
    node->large = "";
  }
}
