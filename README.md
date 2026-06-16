# Tic Tac Toe - C++ Console Project

## Overview

This is a console-based Tic Tac Toe game developed in C++. The main objective of this project is to apply Object-Oriented Programming concepts effectively by separating the game into different classes with clear responsibilities.

The project is currently console-based, but a graphical user interface and additional features will be added in future updates.

## Tech Stack

* Language: C++
* IDE: Visual Studio Code
* Compiler: g++ / MinGW
* Version Control: Git and GitHub

## Main Objective

The purpose of this project is to practice and apply core OOP concepts in C++, including:

* Classes and objects
* Encapsulation
* Separation of responsibilities
* Basic game logic handling
* Modular file structure using header and source files

## Class Structure

### Board Class

The `Board` class is responsible for managing the Tic Tac Toe board.

Main responsibilities:

* Stores the 3x3 game grid
* Displays the board
* Converts user position input into row and column values
* Checks whether a selected position is valid
* Places a player symbol on the board
* Provides access to individual board cells for win/draw checking

### Player Class

The `Player` class stores information related to each player.

Main responsibilities:

* Stores the player's name
* Stores the player's selected symbol
* Provides getter and setter functions for player details
* Displays player information

### Game Class

The `Game` class controls the main game flow.

Main responsibilities:

* Manages both players
* Tracks the current player
* Handles player turns
* Makes moves on the board
* Checks winning conditions
* Checks draw conditions
* Displays the winner or draw result

## Current Features

* Console-based menu
* View game rules
* Start a new game
* Two-player gameplay
* Custom player names
* Custom player symbols
* Input validation for menu choices
* Win detection
* Draw detection
* Option to play again

## Future Improvements

Planned improvements include:

* Adding a graphical user interface
* Improving board display
* Adding score tracking
* Adding single-player mode
* Adding difficulty levels
* Improving input handling
* Adding better project structure using build tools

## How to Build and Run

Compile the project using:

```bash
g++ -std=c++17 main.cpp Board.cpp Game.cpp Player.cpp -o tictactoe
```

Run the program:

```bash
./tictactoe
```

On Windows PowerShell, run:

```powershell
.\tictactoe.exe
```

## Project Status

This project is currently under development. The console-based version is functional, and future versions will include GUI support and additional gameplay features.
