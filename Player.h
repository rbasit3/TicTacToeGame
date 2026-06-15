#pragma once
#include <iostream>
#include <string>
#include "Board.h"
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
    bool MakeMove(Board &board, int position);
    void displayPlayerInfo();

};