#include "Item.h"


    // constructors!
    Item::Item() {
        _name = "";
        _desc = "Thin air";
        _heal = 0;
        _damage = 0;
        _condition = 0;
        _value = 0;
    }

    Item::Item(string name) {
        _name = name;
    }


    Item::Item(string name, string desc) {
        _name = name;
        _desc = desc;
    }

    Item::Item(string name, string desc, int value) {
        _name = name;
        _desc = desc;
        _value = value;
    }

    Item::Item(string name, string desc, int value, int damage) {
        _name = name;
        _desc = desc;
        _value = value;
        _damage = damage;
    }

    Item::Item(string name, string desc, int value, int damage, int heal) {
        _name = name;
        _desc = desc;
        _value = value;
        _damage = damage;
        _heal = heal;
    }

    Item::Item(string name, string desc, int value, int damage, int heal, int condition) {
        _name = name;
        _desc = desc;
        _value = value;
        _damage = damage;
        _heal = heal;
        _condition = condition;
    }


    // deconstructor!
    Item::~Item(){

    }

    void Item::specs() const {
        cout << endl <<
        _name << "(" << _desc << ")" << endl <<
        _value << " Gold" << endl <<
        "Damage:" << _damage << endl <<
        "Heal:" << _heal << endl <<
        "Condition:" << _condition << endl << endl;

    }


    // getters
    string Item::getName() const{
        return _name;
    }
    string Item::getDesc() const{
        return _desc;
    }
    int Item::getValue() const{
        return _value;
    }
    int Item::getDamage() const{
        return _damage;
    }
    int Item::getHeal() const{
        return _heal;
    }
    int Item::getCondition() const{
        return _condition;
    }

    // setters
    void Item::setName(string n){
        _name = n;
    }
    void Item::setDesc(string d){
        _desc = d;
    }
    void Item::setDamage(int d){
        _damage = d;
    }
    void Item::setHeal(int h){
        _heal = h;
    }
    void Item::setCondition(int c){
        _condition = c;
    }

