#include "Player.h"


    Player::Player(){
        _name = "";
        _age = 0;
        _damage = 0;
        _health = 100;
        _armor = 0;
        _gold = 0;
        _alive = 1;
    }


    Player::Player(string n){
        _name = n;
        _gold = 0;
        _alive = 1;
    }
    Player::Player(string n, int a){
        _name = n;
        _age = a;
        _gold = 0;
        _alive = 1;
    }
    Player::Player(string n, int a, int d){
        _name = n;
        _age = a;
        _damage = d;
        _gold = 0;
        _alive = 1;
    }
    Player::Player(string n, int a, int d, int h){
        _name = n;
        _age = a;
        _damage = d;
        _health = h;
        _gold = 0;
        _alive = 1;
    }

    Player::Player(string n, int a, int d, int h, int ar) {
        _name = n;
        _age = a;
        _damage = d;
        _health = h;
        _armor = ar;
        _gold = 0;
        _alive = 1;
    }


    Player::~Player(){

    }

    // Player _User attacks monster
    bool Player::attack(Player enemy) {
        cout << "  -You swing at the " << enemy.getName() << "\n";
        if(randomFlop()) {
            cout << "  +You HIT, with " << this->_damage << "pts of damage!\n";
            enemy.takeDamage(this->_damage);
            return true;
        } else {
            cout << "Miss!\n\n";
            return false;
        }
    }

    // Monster attacks player
    bool Player::attackM(Player enemy) {
        cout << "  -" << enemy.getName() << " jumps out and swings at you!\n";
        if(randomFlop()) {
            cout << "  +HIT, you with " << enemy.getDamage() << "pts of damage!\n";

            return true;
        } else {
            cout << "Miss!\n\n";
            return false;
        }
    }

    void Player::takeDamage(int damage){
        int result = 0;
        result = this-> _health - damage;
        if(result > 0) {
           this-> setHealth(result);
        } else if (result < 1 || result == 0) {
           this-> setHealth(0);
           this-> setAlive(0);
        }
        cout << this->_name << " health is now " << this->_health << "\n";


    }


    void Player::specs(){
        cout << endl << endl <<
        "  " << _name << endl <<
        "  Age:" << _age << endl <<
        "  Damage:" << _damage << endl <<
        "  Health:" << _health << endl <<
        "  Armor:" << _armor << endl <<
        "  Gold:"  << _gold << endl <<
        "  Alive:" << _alive << endl;
    }

    void Player::specsOneline(){
        cout <<
        "Player:" << _name << ", " <<
        "Age:" << _age << ", " <<
        "Damage:" << _damage << ", " <<
        "Health:" << _health << ", " <<
        "Armor:" << _armor << ", " <<
        "Gold:"  << _gold;
    }

    string Player::getName(){
        return _name;
    }
    int Player::getAge(){
        return _age;
    }
    int Player::getHealth(){
        return _health;
    }
    int Player::getDamage(){
        return _damage;
    }
    int Player::getGold(){
        return _gold;
    }
    int Player::getArmor(){
        return _armor;
    }
    bool Player::getAlive(){
        return _alive;
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
    void Player::setArmor(int ar){
        _armor = ar;
    }
    void Player::setAlive(bool alive){
        _alive = alive;
    }

    /**
        returns random flipflop (0 or 1),
        use the division of a larger number to generate more entropy.
    */
    int Player::randomFlop() {
        srand (time(0));
        int ranNum = rand() % 50;
        if (ranNum < 25){
            return 0;
        }
        return 1;
    }

