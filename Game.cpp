#include <iostream>
#include "Game.h"
using namespace std;

Game::Game(Player player1, Player player2){
    this->player1=player1;
    this->player2=player2;
    currentPlayer = &this->player1;
    winner = nullptr;
}
void Game::setCurrentPlayer(Player* player){
    currentPlayer = player;
}
void Game::setWinner(Player* player){
    winner = player;
}
Player* Game::getCurrentPlayer(){
    return currentPlayer;
}
Player* Game::getWinner(){
    return winner;
}