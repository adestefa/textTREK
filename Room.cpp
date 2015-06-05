#include "Room.h"

using namespace std;

    /*

    */
    Room::Room(){
        _name = "Someplace";
        _desc = "";
        _doors[0]= 1;
        _doors[1]= 0;
        _doors[2]= 0; // switch index to match phonic (North,South,East,West)
        _doors[3]= 0;
    }

    Room::Room(string name){
         _name = name;
        _desc = "";
        _doors[0]= 1;
        _doors[1]= 0;
        _doors[2]= 0;
        _doors[3]= 0;
    }

        Room::Room(string name, string desc){
        _name = name;
        _desc = desc;
        _doors[0]= 1;
        _doors[1]= 0;
        _doors[2]= 0;
        _doors[3]= 0;
    }


    Room::Room(string name, string desc, int north, int south, int east, int west){
        _name = name;
        _desc = desc;
        _doors[0]= north;
        _doors[1]= south;
        _doors[2]= east;
        _doors[3]= west;

    }

     Room::Room(string name, string desc, int north, int south, int east, int west, Player monsters[], Item items[]){
        _name = name;
        _desc = desc;
        _monsters[5] = _monsters[5];
        _items[5] = items[5];
        _doors[0]= north;
        _doors[1]= south;
        _doors[2]= east;
        _doors[3]= west;

    }
    string Room::getName() {
        return _name;
    }

    void Room::refeshCounts() {
        int c=0;
        for(int i=0;i<5;i++){
            string n = _monsters[i].getName();
            if(n != ""){
                c++;
            }
        }
        _numOfMonsters = c;

        c=0;
        for(int i=0;i<5;i++){
            string n = _items[i].getName();
            if(n != ""){
                c++;
            }
        }
        _numOfItems = c;

      cout  << " mons:" << _numOfMonsters << " items:" << _numOfItems << endl;
    }





    void Room::getDoors(){
        cout << "[" << _doors[0] << "," << _doors[1] << "," << _doors[2] << "," << _doors[3] << "]\n";

    }

    // returns if this room have a door in a given cardinal direction
    int Room::hasDoor(string direction) {
        if(direction == "north") {
            return _doors[0];
        } else if (direction == "south") {
            return _doors[1];
        } else if (direction == "east") {
            return _doors[2];
        } else if (direction == "west") {
            return _doors[3];
        }
        return 0;
    }
    int Room::hasMonster() {
        refeshCounts();
        return _numOfMonsters;

    }

    void Room::specs() {
        cout << "\n" << _desc << endl;
        refeshCounts();
        getDoors();
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
               // cout << "You find a " << monsters << endl;
            } else if (cnt > 1) {
                cout << "  You find " << cnt << " monsters: " << monsters << endl;
            }

        } else {
            cout << "  No monsters found." << endl;
        }


    }
// report all things in this room
    Player Room::searchRoomForMonsters() {
        string monsters;
        string name;
        Player thisMon;
        int cnt = 0;
        for(int m = 0; m < 5; m++) {
                name = _monsters[m].getName();
                if(name != ""){
                    monsters = monsters + name + " ";
                    thisMon = _monsters[m];
                    cnt++;
                }
        }

        if(cnt > 0){
            if(cnt == 1) {
                cout << "  You find a " << monsters << endl;
            } else if (cnt > 1) {
                cout << "  You find " << cnt << " monsters: " << monsters << endl;
            }
            return thisMon;

        } else {
            cout << "  No monsters found." << endl;
            return Player("null",0,0,0,0);
        }


    }

