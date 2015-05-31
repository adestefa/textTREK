#include "Player.h"


    Player::Player(){
        _name = "";
        _age = 0;
        _damage = 0;
        _health = 0;
        _armor = 0;
        _gold = 0;
    }


    Player::Player(string n){
        _name = n;
        _gold = 0;
    }
    Player::Player(string n, int a){
        _name = n;
        _age = a;
        _gold = 0;
    }
    Player::Player(string n, int a, int d){
        _name = n;
        _age = a;
        _damage = d;
        _gold = 0;
    }
    Player::Player(string n, int a, int d, int h){
        _name = n;
        _age = a;
        _damage = d;
        _health = h;
        _gold = 0;
    }

    Player::Player(string n, int a, int d, int h, int ar) {
        _name = n;
        _age = a;
        _damage = d;
        _health = h;
        _armor = ar;
        _gold = 0;
    }


    Player::~Player(){

    }

    void Player::specs() const {
        cout << endl << endl <<
        "  " << _name << endl <<
        "  Age:" << _age << endl <<
        "  Damage:" << _damage << endl <<
        "  Health:" << _health << endl <<
        "  Armor:" << _armor << endl <<
        "  Gold:"  << _gold << endl;
    }

    void Player::specsOneline() const {
        cout <<
        "Player:" << _name << ", " <<
        "Age:" << _age << ", " <<
        "Damage:" << _damage << ", " <<
        "Health:" << _health << ", " <<
        "Armor:" << _armor << ", " <<
        "Gold:"  << _gold;
    }


    string Player::getName() const{
        return _name;
    }
    int Player::getAge() const{
        return _age;
    }
    int Player::getHealth() const{
        return _health;
    }
    int Player::getDamage() const{
        return _damage;
    }
    int Player::getGold() const{
        return _gold;
    }
    int Player::getArmor() const{
        return _armor;
    }

    void Player::setName(string n){
        _name = n;
    }
    void Player::setAge(int a){
        _age = a;
    }
    void Player::setHealth(int h){
        _health = h;
    }
    void Player::setDamage(int d){
        _damage = d;
    }
    void Player::setGold(int gold){
        _gold = gold;
    }
    void Player::giveGold(int gold){
        _gold = _gold + gold;
    }
    void Player::setAromor(int ar){
        _armor = ar;
    }

