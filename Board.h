#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Board{
    private:
    char grid[3][3];
    public:
    Board();
    void displayBoard();
    bool placeSymbol(int position1, char symbol1);
    int calculatePositionR(int position1);
    int calculatePositionC(int position1);
    bool CheckValidity(int position1);
};