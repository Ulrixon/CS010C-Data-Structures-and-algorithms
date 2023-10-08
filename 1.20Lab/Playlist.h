#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class PlaylistNode
{
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode *nextNodePtr;

public:
    // class constructor
    PlaylistNode(string uid = "none", string songName = "none", string artistName = "none", int songLength = 0,
                 PlaylistNode *nextNodePtrInit = 0);
    void InsertAfter(PlaylistNode *nextNodePtrLoc); // funtions like InsertAfter function on zybook
    void SetNext(PlaylistNode *nextPtr);            // set nextNodePtr = nextPtr
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode *GetNext();
    void PrintPlaylistNode();
};
