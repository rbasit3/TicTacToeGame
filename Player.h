#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player{
    private:
    string name;
    char symbol;
    public:
    Player(string name, char symbol);
    //Setters
    void setName(string name);
    void setSymbol(char symbol);
    //Getters
    string getName();
    char getSymbol();
    void displayPlayerInfo();
};