#include <iostream>
#include <vector>
using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{
    T min;
    unsigned minIndex;
    minIndex = index;
    min = vals.at(index);
    for (int i = index; i < vals.size(); i++) // find the next min and record its index and set it min
    {
        if (vals.at(i) < min)
        {
            min = vals.at(i);
            minIndex = i;
        }
    }
    return minIndex;
}

template <typename T>
vector<T> selection_sort(vector<T> &vals)
{
    unsigned minIndex;
    T tmp; // used for swap
    for (int i = 0; i < vals.size(); i++)
    {
        minIndex = min_index(vals, i);
        tmp = vals.at(i); // swap location i with min
        vals.at(i) = vals.at(minIndex);
        vals.at(minIndex) = tmp;
    }
    return vals;
}

template <typename T>
T getElement(vector<T> vals, int index)
{
    if (index >= vals.size())
    {
        throw runtime_error("out of range exception occured");
    }
    return vals.at(index);
}

vector<char> createVector()
{
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for (int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main()
{

    // Part B
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    try
    {
        while (--numOfRuns >= 0)
        {
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals, index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
    }
    catch (runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
