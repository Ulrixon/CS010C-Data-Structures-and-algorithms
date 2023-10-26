#include "WordLadder.h"
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

WordLadder::WordLadder(const string &filename)
{
    ifstream inFS;
    inFS.open(filename);
    string word;
    if (!inFS.is_open())
    {
        cout << "Could not open file" << endl;
    }
    while (inFS >> word)
    {
        if (word.size() == 5)
        {
            this->dict.push_front(word);
        }
        else
        {
            cout << "word length not equal to 5" << endl;
        }
    }
}

void WordLadder::outputLadder(const string &start, const string &end,
                              const string &outputFile)
{
    if(start == end){
        std::ofstream outfile(outputFile);
        outfile << start;
        return;
    }
    stack<string> frontStack; // create a Stack containing just the first word in the ladder
    string target;
    frontStack.push(start);
    queue<stack<string> > queueOfStack; // enqueue this Stack on to a Queue of Stacks
    queueOfStack.push(frontStack);
    std::list<string>::iterator findIter = std::find(dict.begin(), dict.end(), start);
    if (findIter == dict.end()) // If either word passed in does not exist in the dictionary (dict),this function should output an error message and return.
    {
        cout << "start not exist in dict" << endl;
        return;
    }
    findIter = std::find(dict.begin(), dict.end(), end);
    if (findIter == dict.end())
    {
        cout << "end not exist in dict" << endl;
        return;
    }
    list<string>::iterator it = dict.begin();
    dict.reverse();
    while (queueOfStack.empty() == false)
    {
        target = queueOfStack.front().top();
        frontStack = queueOfStack.front();
        //cout << frontStack.top() << endl;
        
        string word;
        it = dict.begin();
        for (size_t i = 0; i < this->dict.size(); i++) // for all word in dict
        {
            int count = 0; // count same char
            word = it->data();
            for (int j = 0; j < 5; j++)
            {
                if (target[j] == word[j])
                {
                    count++;
                }
            }
            it++;
            if (count == 4) // if the word is off by just one letter from the top word
            {
                stack<string> newStack(frontStack); // create a new Stack that is a copy of the front Stack and push on this off-by-one word found
                newStack.push(word);
                //cout << word << endl;
                if (word == end)
                { // we finished then output to file
                    ;
                    if (std::ifstream (outputFile))
                    {
                        ofstream outfile;
                        outfile.open(outputFile);
                        stack<string> stackForInverse; // stack used for inverse output
                        while (!newStack.empty())
                        {
                            stackForInverse.push(newStack.top());
                            // outfile << newStack.top() << endl;
                            newStack.pop();
                    }
                    while (!stackForInverse.empty())
                    {
                        outfile << stackForInverse.top() << endl;
                        stackForInverse.pop();
                    }
                    }
                    else{
                        std::ofstream outfile(outputFile);
                        stack<string> stackForInverse; // stack used for inverse output
                    while (!newStack.empty())
                    {
                        stackForInverse.push(newStack.top());
                        //outfile << newStack.top() << endl;
                        newStack.pop();
                    }
                    while (!stackForInverse.empty())
                    {
                        outfile << stackForInverse.top() << endl;
                        stackForInverse.pop();
                    }
                    }
                    
                    

                    return ;
                }
                else
                { // otherwise, enqueue this new Stack and remove this word from the dictionary
                    queueOfStack.push(newStack);
                    dict.remove(word);
                }
            }
        }
        queueOfStack.pop(); // dequeue this front stack
    }
    // if the Queue is empty and you didn't find the word ladder, a word ladder does not exist for these 2 words
    std::ofstream outfile(outputFile);
    outfile << "No Word Ladder Found.";
}