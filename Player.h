#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

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

    void specs() const;
    void specsOneline() const;

    string getName() const;
    int getAge() const;
    int getHealth() const;
    int getDamage() const;
    int getGold() const;
    int getArmor() const;

    void setName(string n);
    void setAge(int a);
    void setHealth(int h);
    void setDamage(int d);
    void setGold(int g);
    void setAromor(int ar);


private:
	string _name;
	int _age;
	int _health;
	int _armor;
	int _damage;
	int _gold;


};
#endif

