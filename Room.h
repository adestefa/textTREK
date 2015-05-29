#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Item.h"

using namespace std;

/*

*/
class Room
{
public:

    // constructors
    Room();
    // desc
    Room(string);
    // desc, north, south, east, west
    Room(string , int, int, int, int);
    Room(string , int, int, int, int, Player[], Item[]);

    //what's in the room?
    string _desc;
    Player _monsters[5];
    Item _items[5];
    int _doors[5];
    int _numOfMonsters;
    int _numOfItems;

    // member functions
    int hasDoor(string);
    void searchRoom();
    void specs();
    void refeshCounts();

private:

};
#endif
