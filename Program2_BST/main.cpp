#include <iostream>
#include <limits>
#include "BSTree.h"


using std::cerr;
using std::cout;
using std::endl;
using std::string;

void run_tests() // has been disable 
{
    cout << "Constructing BS Tree...";
    BSTree bst = BSTree();
    cout << "complete." << endl;

    int totalTests = 0, failedTests = 0;
    totalTests++;
    cout << "Test: testing largest on empty tree...";
    if (bst.largest() == "")
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }
    totalTests++;
    cout << "Test: testing smallest on empty tree...";
    if (bst.smallest() == "")
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }
    /* Test insert (assume search works) */
    totalTests++;
    cout << "Test: testing insert and search...";
    string test_input = "Hello";
    bst.insert(test_input);
    if (bst.search(test_input))
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert second word and search first and second...";
    string test_input2 = "World";
    bst.insert(test_input2);
    if (bst.search(test_input) && bst.search(test_input2))
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert duplicate and search first (duplicate) and second...";
    string test_input_duplicate = "Hello";
    bst.insert(test_input_duplicate);
    if (bst.search(test_input) && bst.search(test_input2))
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing remove duplicate and search first (duplicate) second...";
    bst.remove(test_input);
    if (bst.search(test_input))
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing remove first (now gone)...";
    bst.remove(test_input);
    if (!bst.search(test_input) && bst.search(test_input2))
    {
        cerr << "Passed" << endl;
    }
    else
    {
        cerr << "Failed" << endl;
        failedTests++;
    }

    // TODO: Add tests for largest and smallest on non-empty trees
    // TODO: Add tests for insert and remove on larger trees
    // TODO: Add tests for height of nodes (empty and larger trees)
    // Manually inspect pre post and inorder traversals

    cout << "Passed " << totalTests - failedTests << " / " << totalTests << " tests." << endl;
}

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

int menu()
{
    int choice = 0;
    cout << endl
         << "Enter menu choice: ";
    cout << endl;
    cout
        << "1. Insert" << endl
        << "2. Remove" << endl
        << "3. Print" << endl
        << "4. Search" << endl
        << "5. Smallest" << endl
        << "6. Largest" << endl
        << "7. Height" << endl
        << "8. Quit" << endl;
    cin >> choice;
    if(cin.fail())
    {
        throw runtime_error("input fail.");
    }
    //cin >> choice;

    // fix buffer just in case non-numeric choice entered
    // also gets rid of newline character
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main()
{
    // Pass all your tests before running the executable main
    // run_tests();  // TODO: Remove before submitting
    //return 0;

    BSTree *tree = new BSTree();
    try
    {
    int choice = menu();

    string entry;
    
        while (choice != 8)
        {

            if (choice == 1)
            {
                cout << "Enter string to insert: " << endl;
                
                getline(cin, entry);
                if (cin.fail())
                {
                    throw runtime_error("input failure");
                }
                tree->insert(entry);
            }
            else if (choice == 2)
            {
                cout << "Enter string to remove: " << endl;
                getline(cin, entry);
                if (cin.fail())
                {
                    throw runtime_error("input failure");
                }
                tree->remove(entry);
            }
            else if (choice == 3)
            {
                printOrders(tree);
            }
            else if (choice == 4)
            {
                cout << "Enter string to search for: " << endl;
                getline(cin, entry);
                if (cin.fail())
                {
                    throw runtime_error("input failure");
                }
                if(tree->search(entry) == false)
                {
                    cout << "Not Found" << endl;
                }
                else
                {
                    cout << "Found" << endl;
                }
                
            }
            else if (choice == 5)
            {
                cout << "Smallest: ";
                cout << tree->smallest() << endl;
            }
            else if (choice == 6)
            {
                cout << "Largest: ";
                cout << tree->largest() << endl;
            }
            else if (choice == 7)
            {
                
                cout << "Enter string: " << endl;
                getline(cin, entry);
                if (cin.fail())
                {
                    throw runtime_error("input failure");
                }
                cout << "Height of subtree rooted at " << entry << ": " << tree->height(entry) <<endl;
            }
            else if (choice == 8)
            {
                break;
            }
            
            // fix buffer just in case non-numeric choice entered
            choice = menu();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    delete tree;
    return 0;
}
