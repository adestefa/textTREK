#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>


using namespace std;

class Player
{
public:
    Player();
    Player(string);
    Player(string, int);
    Player(string, int, int);
    Player(string, int, int, int);
    Player(string, int, int, int, int);

    ~Player();


    // behaviors
    void specs();
    void specsOneline();
    bool attack (Player enemy);
    bool attackM (Player enemy); // monster attack
    void takeDamage(int damage);
    int randomFlop();
    void die();

    // Getters
    string getName();
    int getAge();
    int getHealth();
    int getDamage();
    int getGold();
    int getArmor();
    bool getAlive();

    // Setters
    void setName(string n);
    void setAge(int a);
    void setHealth(int h);
    void setDamage(int d);
    void setGold(int gold);
    void giveGold(int gold);
    void setArmor(int ar);
    void setAlive(bool alive);

private:
	string _name;
	int _age;
	int _health;
	int _armor;
	int _damage;
	int _gold;
	bool _alive;


};
#endif

