#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  Tree(const Tree &) = delete;            // prohibit copy
  Tree &operator=(const Tree &) = delete; // prohibit copy assignment
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search(const string &) const;

private:
  // Add additional functions/variables here
  bool isFull(Node *) const; // check if this node is full
  Node *split(Node *, const string &); // split the full node with another key
  Node *insertUpward(Node *, const string &); // push node upward when spliting
  Node *
  findInsertPosition(const string &); // find the leaf where we should insert
  void PrintInorder(Node *currNode) const;
  void PrintPreorder(Node *currNode) const;
  void PrintPostorder(Node *currNode) const;
  Node *findRemovePosition(const string &key);
  void recursiveRemove(Node *currNode);
};

#endif