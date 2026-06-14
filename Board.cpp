#include <iostream>
#include "Board.h"
#include <stdexcept>
#include <string>
using namespace std;

Board::Board(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            grid[i][j] = ' ';
        }
    }
}
void Board::displayBoard(){
    for(int i=0; i<3; i++){
        cout << "|";
        for(int j=0; j<3; j++){
            cout << grid[i][j] << "|";
        }
        cout << endl;
    }
}
int Board::calculatePositionR(int position){
   if(position>0 && position<4){
    return 0;
   }
   if(position>3 && position<7){
    return 1;
   }
    if(position>6 && position<10){
     return 2;
    }
    else{ 
        return -1;
    }
//an integer is always returned. impossible case.validity is checked before this function is called.
}
int Board::calculatePositionC(int position){

    if(position%3==0){
        return 2;
    }
    if(position%3==1){
        return 0;
    }
    if(position%3==2){
        return 1;
    }
    else{
        return -1;
    }
    //an integer is always returned. impossible case.validity is checked before this function is called.
}
bool Board::CheckValidity(int position){
    if(position<1 || position>9){
    throw std::invalid_argument("Invalid position");
    }
    int row = calculatePositionR(position);
    int col = calculatePositionC(position);
    if(grid[row][col] == ' '){
        return true;
    }
    return false;
}
bool Board::placeSymbol(int position, char symbol){
    if(CheckValidity(position)){
        int row = calculatePositionR(position);
        int col = calculatePositionC(position);
        grid[row][col] = symbol;
        return true;
    }
    return false;
}
