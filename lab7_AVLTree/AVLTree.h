#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"
#include <string>

class AVLTree {
private:
  Node *root;
  
public:
  AVLTree();
  ~AVLTree();
  AVLTree(const AVLTree &) = delete;            // prohibit copy
  AVLTree &operator=(const AVLTree &) = delete; // prohibit copy assignment
  void insert(const string &);
  int balanceFactor(Node *);
  void printBalanceFactors();
  void visualizeTree(const string &);

private:
  Node *findUbalancedNode(Node *);
  void rotate(Node*);
  void rotateLeft(Node*);
  void rotateRight(Node*);
  void printBalanceFactors(Node *);
  void visualizeTree(ofstream &, Node *);
      
} ;
#endif
