#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#include "Item.h"
#include "Room.h"
#include <vector>
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

// *********************************
// game helper functions
// *********************************
void start();   // starts game
void welcome(); // msg
void showMap();
void song1();
void flashScreen();
void giveGold(int gold);
void textTREK();
void startup();
void createMap();
void playerDeath();
void populateWorld();
int randomFlop();
void getUserInput();
void playWindowsChime();
bool processCMD(string cmd);
void draw(string ascii_art_file);
void setBackground(string color);
int randomNumber(int start, int limit);


string getFileContents (std::ifstream& File);

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
string _VER = "0.2.5";
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

// the user object
Player _User;

// stores the room the user is in
int _ROOM_POINTER_A = 0;
int _ROOM_POINTER_B = 0;


// loading delay
int _GAME_LOADING_DELAY = 10;

// show loading progress bars when true
bool _GAME_SHOW_LOADING = true;

// list of room descriptions
int _NUM_ROOM_DESC = 6;
string _ROOM_DESC[6];


string _GAME_ART_CHEST_OPEN = "_GAME_ART_CHEST_OPEN_1.txt";
string _GAME_ART_CHEST_OPEN_2 = "_GAME_ART_CHEST_OPEN_2.txt";
string _GAME_ART_CHEST_CLOSED = "_GAME_ART_CHEST_CLOSED_1.txt";

bool _GAME_OVER = false;
bool _GAME_RESTART = false;

// *********************************
// Do the work!
// *********************************

int main()
{
    srand ( time(0) );
    textTREK();
	system("PAUSE");
	return 0;
}

void textTREK() {
    system("CLS");
    song1();
    // Homage to War Games Movie
    cout << "\n\nShall we play a game?";
    // user input
    string in;
    cin >> in;
    // development back door, skip intro for faster testing
    if(in == "dev") {
         _GAME_SHOW_LOADING = false;
         populateWorld();
         createMap();
         startup();

    // all valid "yes" responses (user wants to play game)
    } else if(in == "y" || in == "Y" || in == "yes" || in == "YES" || in == "Yes" || in == "YEs") {
        // set up game world
        welcome();
        populateWorld();
        Beep(56, 100);
        createMap();
        Beep(56, 100);
        setBackground("grey");
        Beep(56, 100);
        // start the game
        startup();

    // user quit
    } else {
        cout << "\nQuitting so soon? At least you now have something in common with Sara Palin";
        cout << "\n\nbye.\n";
    }

}

void playerDeath() {
    system("CLS");
    Beep(57, 100);
    Beep(45, 100);
    Beep(54, 1000);
    setBackground("red");
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t";
    cout << "YOU DIED!";
    cout << "\n\n\t\t\t\tContinue?";

    string in;
    cin >> in;
    if(in == "y" || in == "Y" || in == "yes" || in == "YES" || in == "Yes" || in == "YEs") {
        system("CLS");
        setBackground("grey");
        _GAME_RESTART = true;
    } else {
        setBackground("grey");
        _GAME_OVER = true;
    }
}



// *********************************
// startup and text input functions
// *********************************

/**
    Game splash screen, name and legal
*/
void welcome() {
    system("CLS");
    string msg = "\n                textTREK v" + _VER + "\n\n";
    msg = msg + "textTREK: A Simple Text Adventure\n";
    msg = msg + "Copyright (c) 2015 Bitrot, Inc\n";
    msg = msg + "textTREK is a registered trademark of Bitrot, Inc.\n\n";
    cout << msg;
}



/**
    Start game loop
*/
void startup() {
    setBackground("black");
    system("CLS");
    cout << "\n\n           ADVENTURE AWAITS!\n\n";
    cout << "\n What do they call you?>";
    Beep(45, 1000);

    string playerName;
    cin >> playerName;
    cout << "\n";
    _User = randomPlayer();
    _User.setName(playerName);
    _User.specs();
    cout << "\n\n Now it begins...\n\n";
    system("PAUSE");
    system("cls");
    cout << "\n\n\nYou are standing in an open field, the sun is setting\n in the West and there is a cave to your East.\n\n";

    getUserInput();



}
/**
    function to receive user commands
     - called recursively until 'exit' command is found
*/
void getUserInput() {
    if(_GAME_RESTART) {
          textTREK();
    } else {
        Beep(45, 800);
        string in = "reset";
        getline(cin, in);
        bool exitCMD = processCMD(in);
        // moved prompt here to avoid empty duplicate on startup
        cout << "\n" << _CMD_PROMPT;
        // continue to process input until exit command found
        if (!_GAME_OVER && !exitCMD) {
            getUserInput();
        }
    }
}

/**
    Token Parser
    here we process user input and translate into game commands
*/
bool processCMD(string cmd) {

    // we will quit the game when true
    bool exitCMD = false;

    // Make sure input is not empty
    if(cmd == "" || cmd.empty()){
       // cout << "\nSorry, that is not a valid command.\n";


    // -- GAME COMMANDS ---
    } else if(cmd == "go north"){
        cout << "You head north...\n";

    } else if(cmd == "go south"){
        cout << "You head south...\n";

    } else if(cmd == "go east"){
        cout << "You head east...\n";

    } else if(cmd == "go west"){
        cout << "You head west\n";

    } else if (cmd == "clear") {
        system("CLS");

    } else if(cmd == "reset"){
        cout << "reset\n";
        setBackground("black");

    } else if(cmd == "flee"){
	cout << "As a true coward, you scuttle away.";

    } else if(cmd == "stats"){
         _User.specs();

    } else if(cmd == "search"){
        cout << "You search around the room...\n";

    } else if(cmd == "attack"){
       cout << "You raise your sword and start screaming as you lunge at your opponent.\n";

    } else if(cmd == "help"){
        cout << "valid commands: 'North', 'South', 'East', 'West', 'pickup' \n\n";


    // **secret commands**
    // map test
    } else if (cmd == "map") {
         showMap();
    } else if (cmd == "die") {
        playerDeath();
        cmd = "exit";

    } else if(cmd == "summon chest"){
        draw(_GAME_ART_CHEST_CLOSED);
    } else if(cmd == "unlock chest"){
        draw(_GAME_ART_CHEST_OPEN_2);

    // color tests
    } else if (cmd == "red") {
       setBackground("red");
    } else if (cmd == "green") {
       setBackground("green");
    } else if (cmd == "grey") {
       setBackground("grey");
    } else if (cmd == "black") {
       setBackground("black");
    // play the windows chime sound
    } else if (cmd == "chime") {
       playWindowsChime();


    // user wants to quit, exit the game.
    } else if(cmd == "quit"){
        cout << "Giving up is it? OK, well see ya later.\n";
        exitCMD = true;

    } else if(cmd == "exit"){
        cout << "bye.\n";
        exitCMD = true;

    }
    return exitCMD;
}


// *********************************
// Helper functions
// *********************************

void draw(string ascii_art_file) {
    //std::ifstream Reader;
    if(ascii_art_file == _GAME_ART_CHEST_OPEN){
        std::ifstream Reader("_GAME_ART_CHEST_OPEN_1.txt");
        std::string Art = getFileContents (Reader);       //Get file
        std::cout << Art << std::endl;               //Print it to the screen
        Reader.close ();                  //Open file
        giveGold(50);
    } else if(ascii_art_file == _GAME_ART_CHEST_OPEN_2){
        std::ifstream Reader("_GAME_ART_CHEST_OPEN_2.txt");
        std::string Art = getFileContents (Reader);       //Get file
        std::cout << Art << std::endl;               //Print it to the screen
        Reader.close ();                  //Open file
        giveGold(100);

    } else if(ascii_art_file == _GAME_ART_CHEST_CLOSED){
        std::ifstream Reader("_GAME_ART_CHEST_CLOSED_1.txt");
        std::string Art = getFileContents (Reader);       //Get file
        std::cout << Art << std::endl;               //Print it to the screen
        Reader.close ();

    }

}

void giveGold(int gold){

      cout << "You found " << gold << " gold!\n";
     _User.giveGold(gold);
     flashScreen();
}

void flashScreen(){
    setBackground("grey");
    Sleep(300);
    setBackground("black");
}

// show a progress bar when waiting
void waitProgressBar(string desc, int duration){
    if (_GAME_SHOW_LOADING) {
        cout << "\n" << desc << " [";
        for(int i=0;i<duration;i++) {
                cout << "*";
                Sleep (300);
        }
        cout << "] Complete!\n";
    }
}

// print out double array of room objects for debugging
void showMap() {
    cout << "MAP REPORT\n";
    for(int i=0;i<4;i++){
        for(int b=0;b<4;b++){
            cout << "Room#:" << i << "|" << b << endl;
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
// play windows chime sound (windows machines only)
void playWindowsChime() {
    cout<<"\a\a\a\a\a\a\a";
}


// *********************************
// randomizer object factories
// *********************************

Player randomPlayer() {
    cout << "\n" << "Generating random character [";
    int age = randomNumber(15, 40);
    int damage = randomNumber(5, 15);
    int health = 50;
    int armor = randomNumber(5, 20);
    Player p("r", age, damage, health, armor);
    cout << "] Completed!";
    return p;
}
Player randomMonster() {
    return _WORLD_MONSTERS[randomNumber(0, 4)];
}
Item randomItem() {
    return _WORLD_ITEMS[randomNumber(0, 3)];
}
//Returns a Room object with random contents
Room randomRoom(int north, int south, int east, int west) {


    // generate a Room object with a random description and defined doors
    Room r(_ROOM_DESC[randomNumber(0, _NUM_ROOM_DESC)], north, south, east, west);

    // randomly add random monster
    if(randomFlop()) {
        // add monsters
        r._monsters[0] = randomMonster();
    }

    // randomly add random item
    if(randomFlop()) {
        // add items
        r._items[0] = randomItem();
     }

    // return the Room
    return r;
}

// given a limit integer, and if you should omit zero, will return a random number between 1 and 'limit'
int randomNumber(int start, int limit) {
     Sleep(_GAME_LOADING_DELAY);
    cout << "*";
    int ranNum = rand() % limit; // does the work
    if (ranNum < start) {
        return start;
    }
    return ranNum;

}



// returns 0 or 1,
// use the division of a larger number to
// generate more entropy.
int randomFlop() {
    Sleep(_GAME_LOADING_DELAY);
    int ranNum = rand() % 50;
    if (ranNum < 25){
     return 0;
    }
    return 1;
}

void populateWorld() {
// ____________________
    // populate world items
    // --------------------
	waitProgressBar("Populating world items", 4);
    _WORLD_ITEMS[0] = Item("Potion of Healing", "Drink this potion to heal thyself", 100, 0, 100, 100);
    _WORLD_ITEMS[1] = Item("Sword of Shadows", "Kills undead", 200, 40, 0, 78);
    _WORLD_ITEMS[2] = Item("Shield of Blocking", "A durable shield that can block heavy blows", 300, 0, 0, 30);
    _WORLD_ITEMS[3] = Item("Wooden chair", "Just a boring chair", 30, 3, 0, 58);
    //cout << "Item loading complete!\n";
    Beep(56, 100);
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
    //cout << "Monster loading complete!\n";

    // random room descriptions
     _ROOM_DESC[0]="A dark room lit with a torch on the North wall";
     _ROOM_DESC[1]="The smell of Orc is strong in this damp room";
     _ROOM_DESC[2]="A large room with a tapestry on the South wall and a bookshelf and candle on the North. In the center of the room is a large table with eight chairs.";
     _ROOM_DESC[3]="A coat of arms is on the East wall";
     _ROOM_DESC[4]="The North wall is covered with moss. There is a ";
     _ROOM_DESC[5]="The room appears empty other than a table with a platter. The smell of death and stale bread fills your nose.";
}


void createMap(){

    cout << "\n" << "Creating world map" << " [";
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
    cout << "] Complete!\n";

}


void song1() {
    Beep(56, 100);
    Beep(13, 100);
    Beep(54, 100);
    Beep(52, 100);
    Beep(57, 100);
    Beep(45, 100);
    Beep(54, 1000);
}


std::string getFileContents (std::ifstream& File)
{
    std::string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
	while (File.good ())
	{
	    std::string TempLine;                  //Temp line
	    std::getline (File , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline character

	    Lines += TempLine;                     //Add newline
	}
	return Lines;
    }
    else                           //Return error
    {
	return "ERROR File does not exist.";
    }
}


/**
void gotoXY(int x, int y, string text)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
	cout << text;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
}
*/
