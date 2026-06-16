#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

void displayMenu() {
    cout << "\n\n" << endl;
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║        TIC TAC TOE - MAIN MENU         ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n1. View Rules" << endl;
    cout << "2. Start New Game" << endl;
    cout << "3. Exit" << endl;
    cout << "\nEnter your choice (1-3): ";
}

void displayRules() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║        TIC TAC TOE - GAME RULES        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n1. BASIC RULES:" << endl;
    cout << "   - The game is played on a 3x3 grid" << endl;
    cout << "   - Player 1 plays as X, Player 2 plays as O" << endl;
    cout << "   - Players take turns placing their symbol on empty cells" << endl;
    cout << "   - A cell is selected by entering its position (1-9)" << endl;
    cout << "\n   Grid positions:" << endl;
    cout << "   1 | 2 | 3" << endl;
    cout << "   ---------" << endl;
    cout << "   4 | 5 | 6" << endl;
    cout << "   ---------" << endl;
    cout << "   7 | 8 | 9" << endl;
    cout << "\n2. WINNING CONDITIONS:" << endl;
    cout << "   - Win by getting 3 of your symbols in a row (horizontal)" << endl;
    cout << "   - Win by getting 3 of your symbols in a column (vertical)" << endl;
    cout << "   - Win by getting 3 of your symbols diagonally" << endl;
    cout << "\n3. DRAW:" << endl;
    cout << "   - If all 9 cells are filled and no player has won, the game is a draw" << endl;
    cout << "\n════════════════════════════════════════\n" << endl;
}

string getPlayerName(int playerNum) {
    string name;
    while(true) {
        cout << "Enter name for Player " << playerNum << " (X): ";
        getline(cin, name);
        
        // Validate that name is not empty
        if(name.empty() || name.find_first_not_of(" \t") == string::npos) {
            cout << "Name cannot be empty! Please try again." << endl;
            continue;
        }
        return name;
    }
}

int main(){
    int choice;
    bool playAgain = true;
    
    while(playAgain) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the input buffer
        
        switch(choice) {
            case 1:
                displayRules();
                break;
                
            case 2: {
                cout << "\n╔════════════════════════════════════════╗" << endl;
                cout << "║       STARTING NEW GAME - SETUP         ║" << endl;
                cout << "╚════════════════════════════════════════╝\n" << endl;
                
                displayRules();
                
                cout << "════════════════════════════════════════" << endl;
                cout << "Please enter player names:" << endl;
                cout << "════════════════════════════════════════\n" << endl;
                
                string name1 = getPlayerName(1);
                string name2 = getPlayerName(2);
                
                cout << "\n════════════════════════════════════════" << endl;
                cout << "Game Starting!" << endl;
                cout << "════════════════════════════════════════\n" << endl;
                
                Player player1(name1, 'X');
                Player player2(name2, 'O');
                Game game(player1, player2);
                game.playGame();
                
                cout << "\n════════════════════════════════════════" << endl;
                cout << "Game Over!" << endl;
                cout << "════════════════════════════════════════\n" << endl;
                
                char playAgainChoice;
                cout << "Would you like to play again? (y/n): ";
                cin >> playAgainChoice;
                cin.ignore(); // Clear the input buffer
                
                if(playAgainChoice != 'y' && playAgainChoice != 'Y') {
                    playAgain = false;
                }
                break;
            }
            
            case 3:
                cout << "\nThank you for playing Tic Tac Toe! Goodbye!" << endl;
                playAgain = false;
                break;
                
            default:
                cout << "\nInvalid choice! Please enter 1, 2, or 3." << endl;
                break;
        }
    }
    
    return 0;
}