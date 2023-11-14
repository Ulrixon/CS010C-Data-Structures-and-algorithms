#include "BSTree.h"
#include <iostream>
#include <limits>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

void printOrders(BSTree *tree) // print all orders
{
  cout << "Preorder = ";
  tree->preOrder();
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder();
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder();
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout << "1. Insert" << endl
       << "2. Remove" << endl
       << "3. Print" << endl
       << "4. Search" << endl
       << "5. Smallest" << endl
       << "6. Largest" << endl
       << "7. Height" << endl
       << "8. Quit" << endl;
  cin >> choice;
  if (cin.fail()) {
    throw runtime_error("input fail.");
  }
  // cin >> choice;

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

int main() {
  // Pass all your tests before running the executable main
  // run_tests();  // TODO: Remove before submitting
  // return 0;

  BSTree *tree = new BSTree();
  try {
    int choice = menu();

    string entry;

    while (choice != 8) {

      if (choice == 1) {
        cout << "Enter string to insert: " << endl;

        getline(cin, entry);
        if (cin.fail()) {
          throw runtime_error("input failure");
        }
        tree->insert(entry);
      } else if (choice == 2) {
        cout << "Enter string to remove: " << endl;
        getline(cin, entry);
        if (cin.fail()) {
          throw runtime_error("input failure");
        }
        tree->remove(entry);
      } else if (choice == 3) {
        printOrders(tree);
      } else if (choice == 4) {
        cout << "Enter string to search for: " << endl;
        getline(cin, entry);
        if (cin.fail()) {
          throw runtime_error("input failure");
        }
        if (tree->search(entry) == false) {
          cout << "Not Found" << endl;
        } else {
          cout << "Found" << endl;
        }

      } else if (choice == 5) {
        cout << "Smallest: ";
        cout << tree->smallest() << endl;
      } else if (choice == 6) {
        cout << "Largest: ";
        cout << tree->largest() << endl;
      } else if (choice == 7) {

        cout << "Enter string: " << endl;
        getline(cin, entry);
        if (cin.fail()) {
          throw runtime_error("input failure");
        }
        cout << "Height of subtree rooted at " << entry << ": "
             << tree->height(entry) << endl;
      } else if (choice == 8) {
        break;
      }

      // fix buffer just in case non-numeric choice entered
      choice = menu();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  delete tree;
  return 0;
}
