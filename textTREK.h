#ifndef TEXTTREK_H
#define TEXTTREK_H


void splashScreen();
void textTREK();
void startup();
void populateWorld();
void createMap();
void getUserInput();
bool processCMD(string cmd);


void song1();
void showMap();
void flashScreen();
void playerDeath();
void giveGold(int gold);
void playWindowsChime();
void draw(string ascii_art_file);
void setBackground(string color);
void waitProgressBar(string desc, int duration);


void nextRoom();
void enterRoom();
void draw_openDoor();
void setRoom(int a, int b);
void tryDoor(string direction);

int randomFlop();
int randomNumber(int start, int limit);
#endif
