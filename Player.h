#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player{
    private:
    string name;
    char symbol;
    int score;
    public:
    Player(string name, char symbol, int score);
    //Setters
    void setName(string name);
    void setSymbol(char symbol);
    void setScore(int score);
    //Getters
    string getName();
    char getSymbol();
    int getScore();
};