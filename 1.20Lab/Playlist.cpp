#include <iostream>
#include <cstdlib>
#include <string>
#include "Playlist.h"
#include <tuple>
using namespace std;

PlaylistNode::PlaylistNode(string uidInit, string songNameInit, // create a new playlistnode
                           string artistNameInit, int songLengthInit, PlaylistNode *nextNodePtrInit)
{
    this->uniqueID = uidInit;
    this->songName = songNameInit;
    this->artistName = artistNameInit;
    this->songLength = songLengthInit;
    this->nextNodePtr = nextNodePtrInit;
}

void PlaylistNode::InsertAfter(PlaylistNode *nextNodePtrLoc) // cannot use for insert before head
{
    PlaylistNode *tmpNext = nullptr;
    tmpNext = this->nextNodePtr;           // Remember next
    this->nextNodePtr = nextNodePtrLoc;    // this -- node -- ?
    nextNodePtrLoc->nextNodePtr = tmpNext; // this -- node -- next
}

void PlaylistNode::PrintPlaylistNode()
{
    cout << "Unique ID: " << this->uniqueID << endl;
    cout << "Song Name: " << this->songName << endl;
    cout << "Artist Name: " << this->artistName << endl;
    cout << "Song Length (in seconds): " << this->GetSongLength() << endl;
}

string PlaylistNode::GetID() const
{
    return this->uniqueID;
}

string PlaylistNode::GetSongName() const
{
    return this->songName;
}

string PlaylistNode::GetArtistName() const
{
    return this->artistName;
}

int PlaylistNode::GetSongLength() const
{
    return this->songLength;
}

PlaylistNode *PlaylistNode::GetNext()
{
    return this->nextNodePtr;
}

void PlaylistNode::SetNext(PlaylistNode *nextPtr)
{
    this->nextNodePtr = nextPtr;
}