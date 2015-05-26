#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#include "Item.h"
#include "Room.h"
#include <vector>
#include <windows.h>


using namespace std;

// *********************************
// game helper functions
// *********************************
void start();   // starts game
void welcome(); // msg
void showMap();
void startup();
void getUserInput();
void playWindowsChime();
bool processCMD(string cmd);
void setBackground(string color);
int randomNumber(int limit, bool omitZero);

void waitProgressBar(string desc, int duration);

// *********************************
// random object factory functions
// *********************************
Item randomItem();
Room randomRoom(int north, int south, int east, int west);
Player randomMonster();
Player randomPlayer();


// *********************************
// game global space
// *********************************

// version
string _VER = "0.1.3";
// command prompt show to user when they type
string _CMD_PROMPT = "$textTREK>";
// global string for all user input
string _input = "";


// global list of all the items in the world
Item _WORLD_ITEMS[4];

// global list of all the monsters in the world
Player _WORLD_MONSTERS[5];

// global double list made up of rooms to map the world
Room _WORLD_MAP[5][5];

// in order to randomly generate rooms
// we need a list of descriptions we can
// randomly select from
string _ROOM_DESC[6];
int _NUM_ROOM_DESC = 6;

// introduce our player hero
Player _User = randomPlayer();


// *********************************
// Do the work!
// *********************************

int main()
{


    welcome(); // display game splash screen and welcome message.
    // ____________________
    // populate world items
    // --------------------
	waitProgressBar("Populating world items", 4);
    _WORLD_ITEMS[0] = Item("Potion of Healing", "Drink this potion to heal thyself", 100, 0, 100, 100);
    _WORLD_ITEMS[1] = Item("Sword of Shadows", "Kills undead", 200, 40, 0, 78);
    _WORLD_ITEMS[2] = Item("Shield of Blocking", "A durable shield that can block heavy blows", 300, 0, 0, 30);
    _WORLD_ITEMS[3] = Item("Wooden chair", "Just a boring chair", 30, 3, 0, 58);
    cout << "Item loading complete!\n";

    // ____________________
    // populate world monsters
    // --------------------
    waitProgressBar("Populating world monsters", 5);
    // (name, age, damage, health, armor)
    _WORLD_MONSTERS[0] = Player("Ghoul", 30, 3, 10, 5);
    _WORLD_MONSTERS[1] = Player("Commander Ghoul", 80, 20, 100, 15);
    _WORLD_MONSTERS[2] = Player("Skeleton", 1000, 10, 20, 4);
    _WORLD_MONSTERS[3] = Player("Orc", 200, 50, 200, 50);
    _WORLD_MONSTERS[4] = Player("Imp", 200, 7, 20, 2);
    cout << "Monster loading complete!\n";

     waitProgressBar("Creating world map", 7);
     // random room descriptions
     _ROOM_DESC[0]="A dark room lit with a torch on the North wall";
     _ROOM_DESC[1]="The smell of Orc is strong in this damp room";
     _ROOM_DESC[2]="A large room with a tapestry on the South wall and a bookshelf and candle on the North. In the center of the room is a large table with eight chairs.";
     _ROOM_DESC[3]="A coat of arms is on the East wall";
     _ROOM_DESC[4]="The North wall is covered with moss. There is a ";
     _ROOM_DESC[5]="The room appears empty other than a table with a platter. The smell of death and stale bread fills your nose.";

     // ____________________
     // map first row
     // --------------------
    _WORLD_MAP[0][0] = randomRoom(0,0,1,0);
    _WORLD_MAP[0][1] = randomRoom(0,0,1,1);
    _WORLD_MAP[0][2] = randomRoom(0,0,1,1);
    _WORLD_MAP[0][3] = randomRoom(0,0,1,0);

    // ____________________
    // map second row
    // --------------------
    _WORLD_MAP[1][0] = randomRoom(0,1,1,0);
    _WORLD_MAP[1][1] = randomRoom(0,1,0,1);
    _WORLD_MAP[1][2] = randomRoom(0,1,1,0);
    _WORLD_MAP[1][3] = randomRoom(1,1,0,1);

    // ____________________
    // map third row
    // --------------------
    _WORLD_MAP[2][0] = randomRoom(1,1,0,0);
    _WORLD_MAP[2][1] = randomRoom(1,1,1,0);
    _WORLD_MAP[2][2] = randomRoom(1,0,1,1);
    _WORLD_MAP[2][3] = randomRoom(1,0,0,1);

    // ____________________
    // map fourth row
    // --------------------
    _WORLD_MAP[3][0] = randomRoom(1,0,0,0);
    _WORLD_MAP[3][1] = randomRoom(1,0,1,0);
    _WORLD_MAP[3][2] = randomRoom(0,0,1,1);
    _WORLD_MAP[3][3] = randomRoom(0,0,0,1);
    cout << "Game world generation complete!\n\n";


    startup();

 	//bool isPlaying = true;
	//while (isPlaying)
	//{
	//	isPlaying = RunGame();
	//}
	system("PAUSE");
	return 0;
}


// *********************************
// startup and text input functions
// *********************************


void welcome() {
    string msg = "\n                textTREK v" + _VER + "\n\n";
    msg = msg + "textTREK: A Simple Text Adventure\n";
    msg = msg + "Copyright (c) 2015 Bitrot, Inc\n";
    msg = msg + "textTREK is a registered trademark of Bitrot, Inc.\n\n";
    cout << msg;
}
void startup() {
    cout << "\n\n           ADVENTURE AWAITS!\n\n";
    cout << "\n First we need to know our hero's new name>";
    string playerName;
    cin >> playerName;
    _User.setName(playerName);
     cout << "\n" << _User.getName() << " has joined the game! generating your new stats...\n";
    _User.specs();
    cout << "\n\n Now it begins...\n\n";
    system("PAUSE");
    system("cls");
    cout << "\n\n\nYou are standing in an open field, the sun is setting in the West and there is a cave to your East.\n\n";
    getUserInput();

}
void getUserInput() {
    string in = "reset";
    getline(cin, in);
    bool exitCMD = processCMD(in);
    // moved prompt here to avoid empty duplicate
    cout << "\n" << _CMD_PROMPT;
    if (!exitCMD) {
        getUserInput();
    }
}
bool processCMD(string cmd) {
    bool exitCMD = false;

    if(cmd == "" || cmd.empty()){
       // cout << "\nSorry, that is not a valid command.\n";

    } else if(cmd == "go north"){
        cout << "You head north...\n";

    } else if(cmd == "go south"){
        cout << "You head south...\n";

    } else if(cmd == "go east"){
        cout << "You head east...\n";

    } else if(cmd == "go west"){
        cout << "You head west\n";

    } else if(cmd == "reset"){
        cout << "reset\n";

    } else if(cmd == "search"){
        cout << "You search around the room...\n";

    } else if(cmd == "attack"){
       cout << "You raise your sword and start screaming as you lunge at your opponent.\n";

    } else if(cmd == "help"){
        cout << "valid commands: 'North', 'South', 'East', 'West', 'pickup' \n\n";

    } else if (cmd == "map") {
         showMap();

    } else if (cmd == "red") {
       setBackground("red");
    } else if (cmd == "green") {
       setBackground("green");
    } else if (cmd == "grey") {
       setBackground("grey");
    } else if (cmd == "black") {
       setBackground("black");
    } else if (cmd == "windows chime") {
       playWindowsChime();


    } else if(cmd == "exit"){
        cout << "Giving up is it? OK, well see ya later.\n";
        exitCMD = true;

    }
    return exitCMD;
}


// *********************************
// Helper functions
// *********************************

void waitProgressBar(string desc, int duration){
    cout << "\n" << desc << " [";
    for(int i=0;i<duration;i++) {
            cout << "*";
             Sleep (500);
    }
    cout << "]\n";
}


void showMap() {
    cout << "MAP REPORT\n";
    for(int i=0;i<4;i++){
        for(int b=0;b<4;b++){
            _WORLD_MAP[i][b].specs();
        }
    }
}
// using this we can signify action, red for damage, green for a winning blow or gold for finding loot.
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
    //TODO: add gold color..
}

void playWindowsChime() {
    cout<<"\a\a\a\a\a\a\a";
}


// *********************************
// randomizer object factories
// *********************************

Player randomPlayer() {
    int age = randomNumber(100, true);
    int damage = randomNumber(30, true);
    int health = 50;
    int armor = randomNumber(30, false);
    Player p("r", age, damage, health, armor);
    return p;
}
Player randomMonster() {
    return _WORLD_MONSTERS[randomNumber(4, false)];
}
Item randomItem() {
    return _WORLD_ITEMS[randomNumber(3, false)];
}
//Returns a Room object with random contents
Room randomRoom(int north, int south, int east, int west) {

    // generate a Room object with a random description and defined doors
    Room r(_ROOM_DESC[randomNumber(_NUM_ROOM_DESC, true)], north, south, east, west);

    // randomly add random monster
    if(randomNumber(1, false)) {
        // add monsters
        r._monsters[0] = randomMonster();
    }

    // randomly add random item
    if(randomNumber(1, false)) {
        // add items
        r._items[0] = randomItem();
     }

    // return the Room
    return r;
}

// given a limit integer, and if you should omit zero, will return a random number between 1 and 'limit'
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
