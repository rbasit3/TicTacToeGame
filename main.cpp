#include <iostream>
#include <string>
#include <cctype>
#include "Game.h"
using namespace std;

void displayMenu() {
    cout << "\n\n" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "|        TIC TAC TOE - MAIN MENU         |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "\n1. View Rules" << endl;
    cout << "2. Start New Game" << endl;
    cout << "3. Exit" << endl;
    cout << "\nEnter your choice (1-3): ";
}

void displayRules() {
                cout << "+----------------------------------------+" << endl;
                cout << "|       STARTING NEW GAME - SETUP        |" << endl;
                cout << "+----------------------------------------+\n" << endl;
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
    cout << "\n+----------------------------------------+\n" << endl;
}

string getPlayerName(int playerNum) {
    string name;
    while(true) {
        cout << "Enter name for Player " << playerNum << ": ";
        getline(cin, name);
        
        // Validate that name is not empty
        if(name.empty() || name.find_first_not_of(" \t") == string::npos) {
            cout << "Name cannot be empty! Please try again." << endl;
            continue;
        }
        return name;
    }
}

char getPlayerSymbol(int playerNum, char forbiddenSymbol = '\0') {
    string input;
    while(true) {
        cout << "Enter symbol for Player " << playerNum << ": ";
        getline(cin, input);

        if(input.empty() || input.find_first_not_of(" \t") == string::npos) {
            cout << "Symbol cannot be empty! Please enter a single character." << endl;
            continue;
        }
        if(input.length() != 1) {
            cout << "Please enter exactly one character for the symbol." << endl;
            continue;
        }

        char symbol = input[0];
        if(isspace(static_cast<unsigned char>(symbol))) {
            cout << "Symbol cannot be whitespace. Please try again." << endl;
            continue;
        }
        if(forbiddenSymbol != '\0' && symbol == forbiddenSymbol) {
            cout << "That symbol is already taken by the other player. Please choose a different symbol." << endl;
            continue;
        }

        return symbol;
    }
}

int main(){
    int choice;
    bool playAgain = true;
    
    while(playAgain) {
        string menuInput;
        // Loop until a valid menu choice (1-3) is entered
        while (true) {
            displayMenu();
            getline(cin, menuInput);

            // Trim leading/trailing spaces
            size_t start = menuInput.find_first_not_of(" \t");
            size_t end = menuInput.find_last_not_of(" \t");
            if (start == string::npos) menuInput = "";
            else menuInput = menuInput.substr(start, end - start + 1);

            if (menuInput.size() == 1 && isdigit(static_cast<unsigned char>(menuInput[0]))) {
                choice = menuInput[0] - '0';
                if (choice >= 1 && choice <= 3) break; // valid
            }

            cout << "\nInvalid choice! Please enter 1, 2, or 3." << endl;
        }

        switch(choice) {
            case 1:
                displayRules();
                break;
                
            case 2: {
                cout << "\n+----------------------------------------+" << endl;
                cout << "|       STARTING NEW GAME - SETUP        |" << endl;
                cout << "+----------------------------------------+\n" << endl;
                
                cout << "+----------------------------------------+" << endl;
                cout << "Please enter player names and symbols:" << endl;
                cout << "+----------------------------------------+\n" << endl;
                
                string name1 = getPlayerName(1);
                char symbol1 = getPlayerSymbol(1);
                cout << endl;
                string name2 = getPlayerName(2);
                char symbol2 = getPlayerSymbol(2, symbol1);
                
                cout << "\n+----------------------------------------+" << endl;
                cout << "Game Starting!" << endl;
                cout << "+----------------------------------------+\n" << endl;
                
                Player player1(name1, symbol1);
                Player player2(name2, symbol2);
                Game game(player1, player2);
                game.playGame();
                
                cout << "\n+----------------------------------------+" << endl;
                cout << "Game Over!" << endl;
                cout << "+----------------------------------------+\n" << endl;
                
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