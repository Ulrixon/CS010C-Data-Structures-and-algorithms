#include <iostream>
#include <tuple>
#include <cstdlib>
#include <string>
#include "Playlist.h"

void PrintMenu(string title)
{
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
}

std::tuple<std::string, std::string, std::string, int> InsertSongInformation()
{
    string newSongUID;
    string newSongName;
    string newArtistName;
    int newSongLength;
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;

    getline(cin, newSongUID);
    if (!std::cin) // check if input fail or not
    {
        if (std::cin.eof())
            std::cout << "EOF\n";
        else
            std::cout << "other failure\n";
    }

    cout << "Enter song's name:" << endl;
    getline(cin, newSongName);
    if (!std::cin) // check if input fail or not
    {
        if (std::cin.eof())
            std::cout << "EOF\n";
        else
            std::cout << "other failure\n";
    }

    // cout << newSongName << endl;
    cout << "Enter artist's name:" << endl;
    getline(cin, newArtistName);
    if (!std::cin) // check if input fail or not
    {
        if (std::cin.eof())
            std::cout << "EOF\n";
        else
            std::cout << "other failure\n";
    }
    cout << "Enter song's length (in seconds):" << endl;

    cin >> newSongLength;
    if (!std::cin) // check if input fail or not
    {
        if (std::cin.eof())
            std::cout << "EOF\n";
        else
            std::cout << "other failure\n";
    }
    cout << endl;
    cin.ignore();
    return {newSongUID, newSongName, newArtistName, newSongLength};
}

int main()
{
    PlaylistNode *headSong = nullptr;
    PlaylistNode *currSong = nullptr;
    PlaylistNode *lastSong = nullptr;
    PlaylistNode *tmpSong = nullptr;
    std::tuple<string, string, string, int> newSongTuple;
    int count = 0; // output counter

    string title;  // playlist title
    string option; // user option store in this
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, title);
    if (!std::cin) // check if input fail or not
    {
        if (std::cin.eof())
            std::cout << "EOF\n";
        else
            std::cout << "other failure\n";
    }

    while (option != "q")
    {
        PrintMenu(title);
        getline(cin, option);
        if (!std::cin) // check if input fail or not
        {
            if (std::cin.eof())
                std::cout << "EOF\n";
            else
                std::cout << "other failure\n";
        }

        if (option == "a") // add song
        {
            if (headSong == nullptr)
            {
                newSongTuple = InsertSongInformation();
                headSong = new PlaylistNode(get<0>(newSongTuple), get<1>(newSongTuple), get<2>(newSongTuple), get<3>(newSongTuple));
                // cout << "test" << headSong->GetSongName() << endl;
                lastSong = headSong;
            }
            else
            {
                newSongTuple = InsertSongInformation();
                currSong = new PlaylistNode(get<0>(newSongTuple), get<1>(newSongTuple), get<2>(newSongTuple), get<3>(newSongTuple));
                lastSong->SetNext(currSong);
                lastSong = currSong;
            }
            lastSong->SetNext(nullptr);
        }
        else if (option == "d") // remove song
        {
            string deleteSongID;
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            // cin.ignore();
            getline(cin, deleteSongID);
            if (!std::cin) // check if input fail or not
            {
                if (std::cin.eof())
                    std::cout << "EOF\n";
                else
                    std::cout << "other failure\n";
            }

            if (headSong->GetID() == deleteSongID)
            { // if we want to delete headSong
                tmpSong = headSong->GetNext();
                cout << "\"" << headSong->GetSongName() << "\""
                     << " removed." << endl;
                cout << endl;
                delete headSong;
                headSong = tmpSong;
            }
            else
            { // delete other song not head
                currSong = headSong;
                while (currSong != nullptr)
                {
                    tmpSong = currSong;
                    currSong = currSong->GetNext();
                    if (currSong->GetID() == deleteSongID)
                    {
                        tmpSong->SetNext(currSong->GetNext());
                        cout << "\"" << currSong->GetSongName() << "\""
                             << " removed." << endl;
                        cout << endl;
                        delete currSong;
                        currSong = nullptr;
                    }
                }
            }
        }
        else if (option == "c") // change position
        {
            int currPosition;
            int newPosition;
            int notFound = 0;
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> currPosition;
            if (!std::cin) // check if input fail or not
            {
                if (std::cin.eof())
                    std::cout << "EOF\n";
                else
                    std::cout << "other failure\n";
            }
            cin.ignore();
            cout << "Enter new position for song:" << endl;
            cin >> newPosition;
            if (!std::cin) // check if input fail or not
            {
                if (std::cin.eof())
                    std::cout << "EOF\n";
                else
                    std::cout << "other failure\n";
            }
            cin.ignore();

            if (currPosition == 1)
            {
                tmpSong = headSong;

                headSong = headSong->GetNext();
                currSong = headSong;
                count = 0; // position count
                while (currSong != nullptr)
                {
                    count++;

                    if (count == newPosition - 1) // find the node before newPosition and insert
                    {
                        currSong->InsertAfter(tmpSong);
                        cout << "\"" << tmpSong->GetSongName() << "\""
                             << " moved to position " << count + 1 << endl;
                        cout << endl;

                        if (tmpSong->GetNext() == nullptr) // check if after insert it is the last one
                        {
                            lastSong = tmpSong;
                        }
                        break;
                    }
                    else if (currSong->GetNext() == nullptr)
                    { // mean this is the end node
                        currSong->InsertAfter(tmpSong);
                        cout << "\"" << tmpSong->GetSongName() << "\""
                             << " moved to position " << count + 1 << endl;
                        cout << endl;
                        if (tmpSong->GetNext() == nullptr) // check if after insert it is the last one
                        {
                            lastSong = tmpSong;
                        }
                        break;
                    }
                    currSong = currSong->GetNext();
                }
            }
            else // other case not change from headSong
            {

                count = 0;
                currSong = headSong;
                while (currSong != nullptr) // find before current position
                {
                    count++;

                    if (count == currPosition - 1)
                    {
                        tmpSong = currSong->GetNext();
                        currSong->SetNext(tmpSong->GetNext()); // remove the song going to change temporarily
                        if (tmpSong->GetNext() == nullptr)
                        { // if the last song going to remove, then change last song to before it
                            lastSong = currSong;
                        }
                        break;
                    }
                    if (currSong->GetNext() == nullptr)
                    { // mean this is the end node
                        cout << "current position not found." << endl;

                        notFound = 1;
                        break;
                    }
                    currSong = currSong->GetNext();
                }

                if (notFound == 1) // not found the currPosition then go back to menu
                {
                    cout << "return to menu" << endl;
                }
                else if (newPosition <= 1) // if new Position is head then use tmpSong insert before headsong
                {
                    tmpSong->SetNext(headSong);
                    headSong = tmpSong;
                    cout << "\"" << tmpSong->GetSongName() << "\""
                         << " moved to position "
                         << "1" << endl;
                    cout << endl;
                }
                else
                {
                    count = 0;
                    currSong = headSong;
                    while (currSong != nullptr)
                    {
                        count++;

                        if (count == newPosition - 1) // find the node before newPosition and insert
                        {
                            currSong->InsertAfter(tmpSong);
                            cout << "\"" << tmpSong->GetSongName() << "\""
                                 << " moved to position " << count + 1 << endl;
                            cout << endl;
                            if (tmpSong->GetNext() == nullptr) // check if after insert it is the last one
                            {
                                lastSong = tmpSong;
                            }
                            break;
                        }
                        else if (currSong->GetNext() == nullptr)
                        { // mean this is the end node and insert
                            currSong->InsertAfter(tmpSong);
                            cout << "\"" << tmpSong->GetSongName() << "\""
                                 << " moved to position " << count + 1 << endl;
                            cout << endl;
                            if (tmpSong->GetNext() == nullptr) // check if after insert it is the last one
                            {
                                lastSong = tmpSong;
                            }
                            break;
                        }
                        currSong = currSong->GetNext();
                    }
                }
            }
        }
        else if (option == "s") // output by specific artist
        {
            string specificArtistName;
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            getline(cin, specificArtistName);
            if (!std::cin) // check if input fail or not
            {
                if (std::cin.eof())
                    std::cout << "EOF\n";
                else
                    std::cout << "other failure\n";
            }
            cout << endl;
            currSong = headSong;
            count = 0;
            while (currSong != nullptr)
            {
                count++;
                if (currSong->GetArtistName() == specificArtistName)
                { // only cout if song writed by specificArtist
                    cout << count << "." << endl;
                    currSong->PrintPlaylistNode();
                    cout << endl;
                }

                currSong = currSong->GetNext();
            }
        }
        else if (option == "t") // output total time
        {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            int totalSec = 0;
            currSong = headSong;
            count = 0;
            while (currSong != nullptr)
            {
                count++;

                totalSec += currSong->GetSongLength();

                currSong = currSong->GetNext();
            }
            cout << "Total time: " << totalSec << " seconds" << endl;
            cout << endl;
        }
        else if (option == "o")
        {
            if (headSong == nullptr)
            {
                cout << title << " - OUTPUT FULL PLAYLIST" << endl;
                cout << "Playlist is empty" << endl;
                cout << endl;
            }
            else
            {
                cout << title << " - OUTPUT FULL PLAYLIST" << endl;
                currSong = headSong;
                count = 0;
                while (currSong != nullptr)
                {
                    count++;
                    cout << count << "." << endl;
                    currSong->PrintPlaylistNode();
                    currSong = currSong->GetNext();
                    cout << endl;
                }
            }
        }
        else if (option == "q")
        {
            exit(0);
        }
        else
        {
        }
    }
}