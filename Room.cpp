#include "Room.h"

using namespace std;

    /*

    */
    Room::Room(){
        _desc = "Empty room";
        _doors[0]= 1;
        _doors[1]= 0;
        _doors[3]= 0; // switch index to match phonic (North,South,East,West)
        _doors[2]= 0;
    }

    Room::Room(string desc){
        _desc = desc;
        _doors[0]= 1;
        _doors[1]= 0;
        _doors[3]= 0;
        _doors[2]= 0;
    }


    Room::Room(string desc, int north, int south, int east, int west){
        _desc = desc;
        _doors[0]= north;
        _doors[1]= south;
        _doors[3]= east;
        _doors[2]= west;

    }

     Room::Room(string desc, int north, int south, int east, int west, Player monsters[], Item items[]){
        _desc = desc;
        _monsters[5] = _monsters[5];
        _items[5] = items[5];
        _doors[0]= north;
        _doors[1]= south;
        _doors[3]= east;
        _doors[2]= west;

    }

    // returns if this room have a door in a given cardinal direction
    int Room::hasDoor(string direction) {
        if(direction == "NORTH") {
                cout << "He wants to go NORTH I say!" << endl;
                return _doors[0];
           } else if (direction == "SOUTH") {
                cout << "HE wants to go South I say!" << endl;
                 return _doors[1];
           } else if (direction == "EAST") {
                cout << "He wants to go EAST I say!" << endl;
                 return _doors[2];
           } else if (direction == "WEST") {
                cout << "He wants to go West I say!" << endl;
                 return _doors[3];
           }
          return 0;
    }

    // report all things in this room
    void Room::searchRoom() {
        string monsters;
        string name;
        int cnt = 0;
        for(int m = 0; m < 5; m++) {
                name = _monsters[m].getName();
                if(name != ""){
                    monsters = monsters + name + " ";
                    cnt++;
                }
        }

        if(cnt > 0){
            if(cnt == 1) {
                cout << "You find a " << monsters << endl;
            } else if (cnt > 1) {
                cout << "You find " << cnt << " monsters: " << monsters << endl;
            }

        } else {
            cout << "No monsters found." << endl;
        }


    }

