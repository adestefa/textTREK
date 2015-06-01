#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Path.h"
#include "textTREK.h"

using namespace std;

string getFileContents (std::ifstream& File);


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
string _VER = "0.3.1";
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



// loading delay
int _GAME_LOADING_DELAY = 10;

// show loading progress bars when true
bool _GAME_SHOW_LOADING = true;

// list of room descriptions
int _NUM_ROOM_DESC = 6;
string _ROOM_DESC[6];


// game art
string _GAME_ART_CHEST_OPEN = "_GAME_ART_CHEST_OPEN_1.txt";
string _GAME_ART_CHEST_OPEN_2 = "_GAME_ART_CHEST_OPEN_2.txt";
string _GAME_ART_CHEST_CLOSED = "_GAME_ART_CHEST_CLOSED_1.txt";
string _GAME_ART_PLAYER_DIED = "_GAME_ART_PLAYER_DIED.txt";

bool _GAME_OVER = false;
bool _GAME_RESTART = false;


// the user object
Player _User;

// stores the room the user is in
int _ROOM_POINTER_A = 0;
int _ROOM_POINTER_B = 0;
Room _GAME_CURRENT_ROOM;


// *********************************
// Do the work!
// *********************************

int main()
{
    srand ( time(0) );
    splashScreen();
	system("PAUSE");
	return 0;
}
void splashScreen() {
        string Art;
        ifstream Reader1("_GAME_ART_TITLE.txt");
        Art = getFileContents (Reader1);       //Get file
        cout << Art << "    v" + _VER + "\n\n";
        Reader1.close();
        populateWorld();
        Beep(56, 100);
        createMap();
        Beep(56, 100);
        flashScreen();
        Beep(56, 100);
        textTREK();
}

/**
    Game loading and start u
*/
void textTREK() {
    // song1();
    // Homage to War Games Movie
    cout << "\n\n    Shall we play a game?\n\n    " << _CMD_PROMPT;
    // user input
    string in;
    cin >> in;
    // all valid "yes" responses (user wants to play game)
    if(in == "y" || in == "Y" || in == "yes" || in == "YES" || in == "Yes" || in == "YEs") {
        // start the game
        startup();
    // user quit
    } else {
        cout << "\nQuitting so soon?";
        cout << "\n\nbye.\n";
    }

}


/**
    Start game loop
*/
void startup() {
    setBackground("black");
    system("CLS");
    cout << "\n\n           ADVENTURE AWAITS!\n\n";
    cout << "\n What do they call you?>";


    string playerName;
    cin >> playerName;
    cout << "\n";
    _User = randomPlayer();
    _User.setName(playerName);
    _User.specs();
    cout << "\n\n Now it begins...\n\n";
    system("PAUSE");
    system("cls");
   // cout << "\n\n\nYou are standing in an open field, the sun is setting\n in the West and there is a cave to your East.\n\n";
    setRoom(0,0);
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
        Beep(56, 100);
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

void tryDoor(string direction) {
    if(_GAME_CURRENT_ROOM.hasDoor(direction)) {
        cout << "You grasp the iron handle and open the door...\n";

        if(direction == "north"){
            int a = (_ROOM_POINTER_A - 1);
            if (a >= 0){
                setRoom(a,_ROOM_POINTER_B);
            } else {
                cout << "The door will not open, there seems to be a problem.\n";
                cout << "data: " << a << "," << _ROOM_POINTER_B << endl;
            }

       } else if(direction == "south"){
            int a = (_ROOM_POINTER_A + 1);
            if (a >= 0){
                setRoom(a,_ROOM_POINTER_B);
            } else {
                cout << "The door will not open, there seems to be a problem.\n";
                cout << "data: " << a << "," << _ROOM_POINTER_B << endl;
            }
       } else if(direction == "east"){
            int b = (_ROOM_POINTER_B + 1);
            if (b >= 0){
                setRoom(_ROOM_POINTER_A,b);
            } else {
                cout << "The door will not open, there seems to be a problem.\n";
                cout << "data: " << _ROOM_POINTER_A << "," << b << endl;
            }
        } else if(direction == "west"){
            int b = (_ROOM_POINTER_A - 1);
            if (b >= 0){
                setRoom(_ROOM_POINTER_A,b);
            } else {
                cout << "The door will not open, there seems to be a problem.\n";
                cout << "data: " << _ROOM_POINTER_A << "," << b << endl;
            }
        } else {
            cout << "Something really bad happened, the door disappeared.\n";
             cout << "data: " << direction << endl;
        }

    } else {
        cout << "There is no door here.\n";

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
         tryDoor("north");
    } else if(cmd == "go south"){
        cout << "You head south...\n";
        tryDoor("south");

    } else if(cmd == "go east"){
        cout << "You head east...\n";
        tryDoor("east");

    } else if(cmd == "go west"){
        cout << "You head west\n";
        tryDoor("west");

    } else if (cmd == "clear") {
        system("CLS");

    } else if(cmd == "reset"){
        cout << "reset\n";
        setBackground("black");

    } else if(cmd == "flee"){
	cout << "As a true coward, you scuttle away.";

    } else if(cmd == "stats"){
         _User.specs();

    } else if(cmd == "open door") {
        draw_openDoor();
    } else if(cmd == "search"){
        cout << "You search around the room";
        Sleep(700);
        cout << ".";
        Sleep(700);
        cout << ".";
        Sleep(700);
        cout << "\nR:" << _ROOM_POINTER_A << "," << _ROOM_POINTER_B << endl;
        cout << _GAME_CURRENT_ROOM._desc << endl;
        _GAME_CURRENT_ROOM.refeshCounts();

     } else if(cmd == "search doors"){
        cout << "Looking for doors";
        Sleep(700);
        cout << ".";
        Sleep(700);
        cout << ".";
        Sleep(700);

         string out;
         string temp;
         int doorCnt = 0;
         if(_GAME_CURRENT_ROOM.hasDoor("north")) {
            temp = temp + " North";
            doorCnt++;
         }
         if(_GAME_CURRENT_ROOM.hasDoor("south")) {
            temp = temp + " South";
            doorCnt++;
         }
         if(_GAME_CURRENT_ROOM.hasDoor("east")) {
            temp = temp + " East";
            doorCnt++;
         }
         if(_GAME_CURRENT_ROOM.hasDoor("west")) {
            temp = temp + " West";
            doorCnt++;
         }

         if (doorCnt > 1) {
            cout << "\nDoors:[" << temp << " ]\n";

         } else if (doorCnt == 1) {
            cout << "\nOnly one door found on the " << temp << " wall.\n";
         }

         _GAME_CURRENT_ROOM.getDoors();


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
    } else if (cmd == "next room") {
        cout << "Enter Room:" << _ROOM_POINTER_A << "," << _ROOM_POINTER_B << endl;
        nextRoom();
    } else if (cmd == "current room") {
        cout << "Room:" << _ROOM_POINTER_A << "," << _ROOM_POINTER_B << endl;
        cout << _GAME_CURRENT_ROOM._desc << endl;
        _GAME_CURRENT_ROOM.refeshCounts();

    } else if (cmd == "set room") {
        cout << "\n First:";
        int a;
        cin >> a;
        cout << "\n Second:";
        int b;
        cin >> b;
        setRoom(a,b);

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
       std::ifstream Reader("_GAME_ART_CHEST_OPEN_1.txt");
        std::string Art = getFileContents (Reader);       //Get file
        std::cout << Art << std::endl;               //Print it to the screen
        Reader.close ();                  //Open file
        giveGold(50);

    /**
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
  */
}

void draw_openDoor() {
     int animation_delay = 300;

     string Art;
     system("CLS");
     ifstream Reader1("_GAME_ART_DOOR_1.txt");
     Art = getFileContents (Reader1);
     cout << Art;
     Reader1.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader2("_GAME_ART_DOOR_2.txt");
     Art = getFileContents (Reader2);
     cout << Art;
     Reader2.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader3("_GAME_ART_DOOR_3.txt");
     Art = getFileContents (Reader3);
     cout << Art;
     Reader3.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader4("_GAME_ART_DOOR_4.txt");
     Art = getFileContents (Reader4);
     cout << Art;
     Reader4.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader5("_GAME_ART_DOOR_5.txt");
     Art = getFileContents (Reader5);
     cout << Art;
     Reader5.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader6("_GAME_ART_DOOR_6.txt");
     Art = getFileContents (Reader6);
     cout << Art;
     Reader6.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader7("_GAME_ART_DOOR_7.txt");
     Art = getFileContents (Reader7);
     cout << Art;
     Reader7.close ();
     Sleep(animation_delay);

     system("CLS");
     ifstream Reader8("_GAME_ART_DOOR_8.txt");
     Art = getFileContents (Reader8);
     cout << Art;
     Reader8.close ();
     Sleep(animation_delay);
     system("CLS");


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

void song1() {
   // Beep(56, 100);
    //Beep(13, 100);
   // Beep(54, 100);
    //Beep(52, 100);
    Beep(57, 100);
    Beep(45, 100);
    Beep(54, 1000);
}

string getFileContents (ifstream& File)
{
    string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
	while (File.good ())
	{
	    string TempLine;                  //Temp line
	    getline (File , TempLine);        //Get temp line
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



// *********************************
// Map and Room related functions
// *********************************


void setRoom(int a, int b) {
     _ROOM_POINTER_A = a;
     _ROOM_POINTER_B = b;
      //cout << "Setting room to " << a << "," << b << endl;
    _GAME_CURRENT_ROOM = _WORLD_MAP[_ROOM_POINTER_A][_ROOM_POINTER_B];
    enterRoom();
}

void enterRoom() {
     system("CLS");
     draw_openDoor();
     flashScreen();
     string desc =  _GAME_CURRENT_ROOM._desc;
     cout << "\n\n\t" << desc << endl;
}

void nextRoom() {

    // load the room into the global var
     _GAME_CURRENT_ROOM = _WORLD_MAP[_ROOM_POINTER_A][_ROOM_POINTER_B];

    // reset the counter if we reach the end of the map
    if(_ROOM_POINTER_A == 4){
        _ROOM_POINTER_A = 0;
    } else {
        _ROOM_POINTER_A++;
    }

   // reset the counter if we reach the end of the map
    if(_ROOM_POINTER_B == 4){
        _ROOM_POINTER_B = 0;
    } else {
        _ROOM_POINTER_B++;
    }

    enterRoom();


}

// print out double array of room objects for debugging
void showMap() {
    cout << "MAP REPORT\n";
    for(int i=0;i<4;i++){
        for(int b=0;b<4;b++){
            cout << "\nRoom#:[" << i << "][" << b << "]";
            _WORLD_MAP[i][b].specs();
        }
    }
}

// *********************************
// randomizer object factories
// *********************************

/**
   Returns a random number between 'start' and 'limit'
*/
int randomNumber(int start, int limit) {
     Sleep(_GAME_LOADING_DELAY);
    cout << "*";
    int ranNum = rand() % limit; // does the work
    if (ranNum < start) {
        return start;
    }
    return ranNum;

}
/**
   returns random flipflop (0 or 1),
   use the division of a larger number to generate more entropy.
*/
int randomFlop() {
    Sleep(_GAME_LOADING_DELAY);
    int ranNum = rand() % 50;
    if (ranNum < 25){
     return 0;
    }
    return 1;
}

/**
  Returns a random monster
*/
Player randomMonster() {
    return _WORLD_MONSTERS[randomNumber(0, 4)];
}

/**
   Returns a random world item
*/
Item randomItem() {
    return _WORLD_ITEMS[randomNumber(0, 3)];
}

/**
   Returns a Room object with random contents
*/
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

/**
   Return a randomly generated player character
*/
Player randomPlayer() {
    cout << "\n" << "  Generating random character [";
    int age = randomNumber(15, 40);
    Sleep(500);
    int damage = randomNumber(5, 15);
    Sleep(500);
    int health = 50;
    int armor = randomNumber(5, 20);
    Sleep(500);
    Player p("r", age, damage, health, armor);
    cout << "] Completed!";
    return p;
}
/**
   Player had died (end game)
*/
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
// World Generation functions
// *********************************



void populateWorld() {
// ____________________
    // populate world items
    // --------------------
	waitProgressBar("    Loading world items", 10);
    _WORLD_ITEMS[0] = Item("Potion of Healing", "Drink this potion to heal thyself", 100, 0, 100, 100);
    _WORLD_ITEMS[1] = Item("Sword of Shadows", "Kills undead", 200, 40, 0, 78);
    _WORLD_ITEMS[2] = Item("Shield of Blocking", "A durable shield that can block heavy blows", 300, 0, 0, 30);
    _WORLD_ITEMS[3] = Item("Wooden chair", "Just a boring chair", 30, 3, 0, 58);
    //cout << "Item loading complete!\n";
    Beep(56, 100);
    // ____________________
    // populate world monsters
    // --------------------
    //waitProgressBar("    Loading monsters", 5);
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
     _ROOM_DESC[2]="A large room with a tapestry on the South wall, and a bookshelf\n and candle on the North. In the center of\n the room is a large table with eight chairs.";
     _ROOM_DESC[3]="A coat of arms is on the East wall";
     _ROOM_DESC[4]="The North wall is covered with moss.";
     _ROOM_DESC[5]="The room appears empty other than a table with a platter. Stale bread fills your nose.";
}


/**
    Define world map as a global double array of Room objects
     - each value will be a random generated room
     - each random room will be given a list of define doors
     - let each be true or false: (north, south, east, west) = (0, 0, 1, 1) = (none, none, door, door)

*/
void createMap(){

    cout << "\n" << "    Creating map" << " [";
     // ____________________
     // map first row
     // --------------------
    _WORLD_MAP[0][0] = randomRoom(0,0,1,0);
    _WORLD_MAP[0][1] = randomRoom(0,0,1,1);
    _WORLD_MAP[0][2] = randomRoom(0,0,1,1);
    _WORLD_MAP[0][3] = randomRoom(0,0,0,1);

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
    cout << "] Complete!\n\n";
    Beep(56, 100);


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
