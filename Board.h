#pragma once
#include <iostream>
#include <string>
using namespace std;

class Board{
    private:
    char grid[3][3];
    int position;
    public:
    Board();
    void displayBoard();
    bool placeSymbol(int position1, char symbol);



};