#include <iostream>
#include <stdexcept>
#include "Game.h"
using namespace std;

Game::Game(Player player1, Player player2): board(), player1(player1), player2(player2), currentPlayer(&this->player1), winner(nullptr) {}
void Game::setCurrentPlayer(Player* player){
    currentPlayer = player;
}
void Game::setWinner(Player* player){
    winner = player;
}
Board& Game::getBoard(){
    return board;
}
Player* Game::getCurrentPlayer(){
    return currentPlayer;
}
Player* Game::getWinner(){
    return winner;
}
 bool Game::MakeMove(Player* current_player, int position)
 {
    if(board.CheckValidity(position)){
        return board.placeSymbol(position, current_player->getSymbol());
    }
    else{
        return false;
    }
 }
 bool Game::handleMove(int position)
{
    if(isGameOver()){
        return false;
    }

    try{
        if(!MakeMove(currentPlayer, position)){
            return false;
        }
    }
    catch(const std::invalid_argument&){
        return false;
    }

    if(checkWin()){
        setWinner(currentPlayer);
        return true;
    }

    if(checkDraw()){
        return true;
    }

    if(currentPlayer == &player1){
        setCurrentPlayer(&player2);
    }
    else{
        setCurrentPlayer(&player1);
    }

    return true;
}
 void Game::displayWinner(){
    if(winner != nullptr){
        cout << "Congratulations " << winner->getName() << "! You win!" << endl;
    }
    else{
        cout << "It's a draw!" << endl;
    }
 }
 void Game::playGame(){
    board.displayBoard();
    while(true){
        // Display current player
        cout << "\n" << currentPlayer->getName() << "'s turn (" << currentPlayer->getSymbol() << ")" << endl;
        cout << "Enter position (1-9): ";
        
        int position;
        cin >> position;
        
        // Validate input
        if(position < 1 || position > 9){
            cout << "Invalid input! Please enter a number between 1 and 9." << endl;
            continue;
        }
        
        // Try to make the move
        if(!MakeMove(currentPlayer, position)){
            cout << "That position is already taken! Please choose another." << endl;
            continue;
        }
        
        // Display the board after the move
        cout << "\n";
        board.displayBoard();
        
        // Check for a winner
        if(checkWin()){
            setWinner(currentPlayer);
            cout << "\n*** " << currentPlayer->getName() << " (" << currentPlayer->getSymbol() << ") wins! ***" << endl;
            displayWinner();
            break;
        }
        
        // Check for a draw
        if(checkDraw()){
            cout << "\n*** The board is full - It's a draw! ***" << endl;
            displayWinner();
            break;
        }
        
        // Switch to the other player
        if(currentPlayer == &player1){
            setCurrentPlayer(&player2);
        }
        else{
            setCurrentPlayer(&player1);
        }
    }
 }
 bool Game::checkDraw()
 { bool FullBoard= false;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board.getCell(i, j) == ' '){
                return false;
            }
             else{
                FullBoard = true;
            }
        }
    }
    if(FullBoard && !checkWin()){
        return true;
    }
    else{
        return false;
    }

 }
    
bool Game::checkWin()
{
    // check horizontal win
    for(int i=0; i<3; i++){
        if(board.getCell(i, 0) == board.getCell(i, 1) && board.getCell(i, 1) == board.getCell(i, 2) && board.getCell(i, 0) != ' '){
            return true;
        }
    }
    // check vertical win
    for(int j=0; j<3; j++){
        if(board.getCell(0, j) == board.getCell(1, j) && board.getCell(1, j) == board.getCell(2, j) && board.getCell(0, j) != ' '){
            return true;
        }
    }
    //check diagonal win (top-left to bottom-right)
    if(board.getCell(0, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 2) && board.getCell(0, 0) != ' '){
        return true;
    }
    //check anti diagonal win (top-right to bottom-left)
    if(board.getCell(0, 2) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 0) && board.getCell(0, 2) != ' '){
        return true;
    }
    return false;
}
bool Game::isGameOver()
{
    return winner != nullptr || checkDraw();
}