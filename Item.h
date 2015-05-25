#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;

/*
    I give the world an item. It can be anything, and do anything you desire.
*/
class Item
{
public:
    // constructors!
    Item();
    Item(string);
    Item(string, string);
    Item(string, string, int);
    Item(string, string, int, int);
    Item(string, string, int, int, int);
    Item(string, string, int, int, int, int);

    // deconstructor!
    ~Item();

    // getters
    string getName() const;
    string getDesc() const;
    int getValue() const;
    int getDamage() const;
    int getHeal() const;
    int getCondition() const;

    void specs() const;

    // setters
    void setName(string n);
    void setDesc(string d);
    void setDamage(int d);
    void setHeal(int h);
    void setCondition(int c);

private:

    // member variables
    string _name;
    string _desc;
    int _value;             // gold value
    int _damage;            // damage points when used as weapon
    int _heal;              // healing points when used as magic
    int _condition;         // physical condition of the object 100% - 0%

};
#endif

