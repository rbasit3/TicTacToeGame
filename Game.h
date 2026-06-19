 #pragma once
#include "Player.h"
#include "Board.h"

class Game{
    private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;
    Player* winner;
    public:
    Game(Player player1, Player player2);
    void setCurrentPlayer(Player* player);
    void setWinner(Player* player);
    Player* getCurrentPlayer();
    Player* getWinner();
    void playGame();
    bool MakeMove(Player* current_player, int position);
    bool checkDraw();
    bool checkWin();
    void displayWinner();
    Board& getBoard();
    bool handleMove(int position);
    bool isGameOver();
};