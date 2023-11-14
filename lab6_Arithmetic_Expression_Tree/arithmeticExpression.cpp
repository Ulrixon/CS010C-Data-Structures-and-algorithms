#include "arithmeticExpression.h"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

arithmeticExpression::arithmeticExpression(const string &input) {
  infixExpression = input;
  root = NULL;
}

void deleteAllNodeInBST(
    TreeNode *currNode) // using recursive function to delete all node starting
                        // from leafs.
{
  if (currNode == NULL) {
    return;
  }

  deleteAllNodeInBST(currNode->left);
  deleteAllNodeInBST(currNode->right);
  delete currNode;
}

arithmeticExpression::~arithmeticExpression() {
  if (root != NULL) {
    deleteAllNodeInBST(root);
  }
}

void arithmeticExpression::buildTree() {
  string postExpression = infix_to_postfix();
  stack<TreeNode *> expressionStack;
  for (size_t i = 0; i < postExpression.size(); i++) // build tree through stack
  {
    if (priority(postExpression.at(i)) == 0) // if digit just add to stack
    {
      TreeNode *node = new TreeNode(postExpression.at(i), (char(65 + i)));
      expressionStack.push(node);
    } else // pop two node from stack and makes them new node's left and right
           // and then push back
    {
      TreeNode *node = new TreeNode(postExpression.at(i), (char(65 + i)));
      node->right = expressionStack.top();
      expressionStack.pop();
      node->left = expressionStack.top();
      expressionStack.pop();
      expressionStack.push(node);
    }
  }
  // assign root to the top of stack
  root = (expressionStack.top());
}

int arithmeticExpression::priority(char op) {
  int priority = 0;
  if (op == '(') {
    priority = 3;
  } else if (op == '*' || op == '/') {
    priority = 2;
  } else if (op == '+' || op == '-') {
    priority = 1;
  }
  return priority;
}

void arithmeticExpression::infix() { infix(root); }

void arithmeticExpression::infix(TreeNode *currNode) {
  if (currNode == NULL || currNode == 0) {
    return;
  }

  if (priority(currNode->data) > 0) {
    cout << "(";
    infix(currNode->left);
    cout << currNode->data;
    infix(currNode->right);
    cout << ")";
  } else {
    infix(currNode->left);
    cout << currNode->data;
    infix(currNode->right);
  }
}

void arithmeticExpression::prefix() { prefix(root); }

void arithmeticExpression::prefix(TreeNode *currNode) {
  if (currNode == NULL || currNode == 0) {
    return;
  }
  cout << currNode->data;
  prefix(currNode->left);
  prefix(currNode->right);
}

void arithmeticExpression::postfix() { postfix(root); }

void arithmeticExpression::postfix(TreeNode *currNode) {
  if (currNode == NULL || currNode == 0) {
    return;
  }

  postfix(currNode->left);
  postfix(currNode->right);
  cout << currNode->data;
}

string arithmeticExpression::infix_to_postfix() {
  stack<char> s;
  ostringstream oss;
  char c;
  for (size_t i = 0; i < infixExpression.size(); i++) {
    c = infixExpression.at(i);
    // cout << c;
    if (c == ' ') {
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' ||
        c == ')') { // c is an operator
      if (c == '(') {
        s.push(c);
      } else if (c == ')') {
        while (s.top() != '(') {
          oss << s.top();
          s.pop();
        }
        s.pop();
      } else {
        while (!s.empty() && priority(c) <= priority(s.top())) {
          if (s.top() == '(') {
            break;
          }
          oss << s.top();
          s.pop();
        }
        s.push(c);
      }
    } else { // c is an operand
      oss << c;
    }
  }
  while (!s.empty()) {
    oss << s.top();
    s.pop();
  }
  return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if (!outFS.is_open()) {
    cout << "Error opening " << outputFilename << endl;
    return;
  }
  outFS << "digraph G {" << endl;
  visualizeTree(outFS, root);
  outFS << "}";
  outFS.close();
  string jpgFilename =
      outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *currNode) {}