#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#include "Item.h"
#include "Room.h"

using namespace std;

void start();   // starts game
void welcome(); // msg
void setBackground(string color);
int randomNumber(int limit, bool omitZero);
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



// introduce our player hero
Player _User = randomPlayer();


int main()
{

    //setBackground("grey");

    welcome();

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
     // sanity test items
	//cout << "Random item generated:";
   // Item item = randomItem();
   // item.specs();
    cout << "generating world map...\n";
    // build the world map
    _WORLD_MAP[0][0] = Room("The room appears empty, but the smell of death fills your nose. You're getting closer!", 1,0,0,0);
    _WORLD_MAP[0][1] = Room("The smell is stronger here", 1,0,0,0);

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
    //setBackground("grey");
    cout << "\n" << _User.getName() << " has joined the game! generating your new stats...\n";
    _User.specs();
    cout << "\n\n Now it begins...\n\n";
    cout << "You are standing in an open field, the sun is setting in the West and there is a cave to your East.\n";
    cout << ">";

}


Player randomPlayer() {
    int age = randomNumber(100, true);
    int damage = randomNumber(30, true);
    int health = 50;
    int armor = randomNumber(30, false);
    Player p("r", age, damage, health, armor);
    return p;
}


Room randomRoom() {
    //srand ( time(NULL) );
    //int RandMonIndex = rand() % 4;
    Room r("Random room");
    r._monsters[0] = randomMonster();
    r._monsters[1] = randomMonster();
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
        system("COLOR ");
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
