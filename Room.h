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
    Room(string, string);
    // desc, north, south, east, west
    Room(string, string, int, int, int, int);
    Room(string, string, int, int, int, int, Player[], Item[]);
    //what's in the room?
    string _name;
    string _desc;
    Player _monsters[5];
    Item _items[5];
    int _doors[5];
    int _numOfMonsters;
    int _numOfItems;
    Player *searchRoomForMonsters();

    // member functions
    int hasDoor(string);
    int hasMonster();
    void getDoors();
    void searchRoom();
    void specs();
    void refeshCounts();
    string getName();

private:

};
#endif
