 #pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "Board.h"
using namespace std;

class Game{
    private:
    Board board;
    Player player1;
    Player player2;
    public:
    Game(Player player1, Player player2);
    void playGame();
    void checkWin();
    void displayWinner(Player winner);
};