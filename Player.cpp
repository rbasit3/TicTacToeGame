#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(string name, char symbol){
    setName(name);
    setSymbol(symbol);
}
void Player::setName(string name){
    this->name = name;
}
void Player::setSymbol(char symbol){
    this->symbol = symbol;
}
string Player::getName(){
    return name;
}
char Player::getSymbol(){
    return symbol;
}
void Player::displayPlayerInfo(){
    cout << "Player Name: " << name << endl;
    cout << "Player Symbol: " << symbol << endl;
}

