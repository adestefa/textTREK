#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#include "Item.h"
#include "Room.h"

using namespace std;


// game helper functions
void start();   // starts game
void welcome(); // msg
void setBackground(string color);
int randomNumber(int limit, bool omitZero);
void getUserInput();

// random object factory functions
Item randomItem();
Room randomRoom();
Player randomMonster();
Player randomPlayer();


// global list of all the items in the world
Item _WORLD_ITEMS[4];

// global list of all the monsters in the world
Player _WORLD_MONSTERS[5];

// global double list made up of rooms to map the world
Room _WORLD_MAP[5][5];

string _ROOM_DESC[6];
int _NUM_ROOM_DESC = 6;

// introduce our player hero
Player _User = randomPlayer();

string _input = "";

int main()
{



    welcome();

    // couts here are verbose but also very helpful with problems loading, you can tell where the issue happened

    cout << "populating world items...\n";
    // populate world items
	_WORLD_ITEMS[0] = Item("Potion of Healing", "Drink this potion to heal thyself", 100, 0, 100, 100);
    _WORLD_ITEMS[1] = Item("Sword of Shadows", "Kills undead", 200, 40, 0, 78);
    _WORLD_ITEMS[2] = Item("Shield of Blocking", "A durable shield that can block heavy blows", 300, 0, 0, 30);
    _WORLD_ITEMS[3] = Item("Wooden chair", "Just a boring chair", 30, 3, 0, 58);

    cout << "populating world monsters...\n";
    // populate world monsters (name, age, damage, health, armor)
    _WORLD_MONSTERS[0] = Player("Ghoul", 30, 3, 10, 5);
    _WORLD_MONSTERS[1] = Player("Commander Ghoul", 80, 20, 100, 15);
    _WORLD_MONSTERS[2] = Player("Skeleton", 1000, 10, 20, 4);
    _WORLD_MONSTERS[3] = Player("Orc", 200, 50, 200, 50);
    _WORLD_MONSTERS[4] = Player("Imp", 200, 7, 20, 2);


     cout << "generating world map...\n";
     _ROOM_DESC[0]="A dark room lit with a torch on the North wall";
     _ROOM_DESC[1]="The smell of Orc is strong in this damp room";
     _ROOM_DESC[2]="A large room with a tapestry on the South wall and a bookshelf and candle on the North. In the center of the room is a large table with eight chairs.";
     _ROOM_DESC[3]="A coat of arms is on the East wall";
     _ROOM_DESC[4]="The North wall is covered with moss. There is a ";
     _ROOM_DESC[5]="The room appears empty other than a table with a platter. The smell of death and stale bread fills your nose.";

     // build the world map
    _WORLD_MAP[0][0] = randomRoom();
    _WORLD_MAP[0][1] = randomRoom();

    //cout << "Random monster generated:";
    //  Player Monster = randomMonster();
    // Monster.specs();

    cout << "\n\n";
    start();

    Room r1 = randomRoom();
    //r1.searchRoom();

	//Player _User;
   // WelcomePlayer(_User);
	//bool isPlaying = true;
	//while (isPlaying)
	//{
	//	isPlaying = RunGame();
	//}
	system("PAUSE");
	return 0;
}


void welcome() {
    string msg = "\n                textTREK\n\n";
    msg = msg + "textTREK: A Simple Text Adventure\n";
    msg = msg + "Copyright (c) 2015 Bitrot, Inc\n";
    msg = msg + "textTREK is a registered trademark of Bitrot, Inc.\nRelease 0.1\n\n";
    msg = msg + "                  ------\n\n";
    cout << msg;
}

void start() {
    cout << "           ADVENTURE AWAITS!\n\n";
    cout << "\n First we need to know our hero's new name>";
    string playerName;
    cin >> playerName;
    _User.setName(playerName);
     cout << "\n" << _User.getName() << " has joined the game! generating your new stats...\n";
    _User.specs();
    cout << "\n\n Now it begins...\n\n";
    system("PAUSE");
    system("cls");
    //setBackground("grey");
    cout << "\n\n\nYou are standing in an open field, the sun is setting in the West and there is a cave to your East.\n";
    cout << "\n\nType --help for help ;-)\n";
    cout << ">";
    getUserInput();
    //setBackground("black");
    system("PAUSE");

}

void getUserInput() {
     cin >> _input;
     if (_input == "--help"){
        cout << "valid commands: 'North', 'South', 'East', 'West', 'pickup' \n\n";
     }

}

Player randomPlayer() {
    int age = randomNumber(100, true);
    int damage = randomNumber(30, true);
    int health = 50;
    int armor = randomNumber(30, false);
    Player p("r", age, damage, health, armor);
    return p;
}

/*
    Returns a Room object with random contents
*/
Room randomRoom() {
    // generate a Room object with a random description
    Room r(_ROOM_DESC[randomNumber(_NUM_ROOM_DESC, true)]);


    if(randomNumber(1, false)) {
        // add monsters
        r._monsters[0] = randomMonster();
    }

    if(randomNumber(1, false)) {
        // add items
        r._items[0] = randomItem();
     }

    // return the Room
    return r;
}


Player randomMonster() {
    srand ( time(NULL) );
    int RandIndex = rand() % 4;
    return _WORLD_MONSTERS[RandIndex];
}


Item randomItem() {
    srand ( time(NULL) ); //initialize the random seed
    int RandIndex = rand() % 3; //generates a random number between 0 and 3
    return _WORLD_ITEMS[RandIndex];
}

void setBackground(string color) {
    if (color == "red"){
        system("COLOR 40"); //red background
    } else if(color == "grey"){
        system("COLOR 70"); // gray background
    } else if(color == "green"){
        system("COLOR 20"); // green background
    } else {
        system("COLOR 07");
    }
}

int randomNumber(int limit, bool omitZero) {
    srand ( time(NULL) );
    int ranNum = rand() % limit; // does the work

    // sometimes you feel like a 'Not' and sometimes you don't
    if(ranNum == 0 && omitZero) {
            return 1;
    } else {
        return ranNum;
    }
}
