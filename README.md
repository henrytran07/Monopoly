# Monopoly-Like Board Game

## Overview

This project implements a Monopoly-like board game with features inspired by the classic board game.

Players can buy properties, upgrade them by building houses and hotels, and engage in buying and selling transactions.

## Features

- Playable board game with a custom board featuring cities from around the world and a property list.
- Automatic property management and transactions.
- Player statistics, including cash and property details, will be displayed in the terminal along with game state tracking.
- Support for multiple players (2 to 6 players).

## Installation

1. **Install Visual Studio Code**: Download and install a compatible version of [Visual Studio Code](https://code.visualstudio.com/).

2. **Questions About IDE Installation**: If you have any questions regarding IDE installation, feel free to contact me via [GitHub](https://github.com/henrytran07).

### Clone the Repository

1. **Clone the Repository**: Clone [Henry's Monopoly Repository](https://github.com/henrytran07/Monopoly) to your local machine.

2. **Select the Directory**: Navigate to the directory where you want to clone the repository:
   ```
   cd [your directory]
    ```
3. **Clone the repository**: Clone the repository into the selected directory: 
```
    git clone https://github.com/henrytran07/Monopoly.git
```
4. **Encounter Issues?** : If you encounter any issues during the process, feel free to contact me. 


## Compiling the program

1. **Navigate to Project's Directory**: Go to the directory where your source files are located. 
```
    cd [your directory]
```

2. **Build the program**: Compile the program using 'make' 
```
    make 
```

3. **Check Executable Files**: Verify that the following files are present in the 'executable' directory. 
    - CommunityChestCard.o
    - MonopolyBoard.o
    - asset.o
    - color_category.o
    - mainImplementation.o
    - money.o
    - virtual_monopoly_board.o

```
    ls executable
```

4. **Link and Create Executable**: Link the object files to create the executable. 

```
    g++ -Wall -std=c++11 -o executable/monopoly_game \
    executable/CommunityChestCard.o \
    executable/MonopolyBoard.o \
    executable/asset.o \
    executable/color_category.o \
    executable/mainImplementation.o \
    executable/money.o \
    executable/virtual_monopoly_board.o

```

5. **Run the program** 

```
    ./executable/monopoly_game
```

6. **Removing the compiled files and cleaning up the build environment**

```
    make clean
```

## Enjoy the Game 

1. **Follow Instructions**: Follow the instructions displayed in the terminal 

2. **Enjoy**: Enjoy the Game!

## Directory Structure

The Monopoly project directory contains the following files and folders:

- **Monopoly/**
  - `README.md`
  - **src/**
    - `CommunityChestCard.cpp`
    - `MonopolyBoard.cpp`
    - `asset.cpp`
    - `color_category.cpp`
    - `mainImplementation.cpp`
    - `money.cpp`
    - `virtual_monopoly_board.cpp`
  - **include/**
    - `CommunityChestCard.h`
    - `MonopolyBoard.h`
    - `asset.h`
    - `color_category.h`
    - `mainImplementation.h`
    - `money.h`
    - `virtual_monopoly_board.h`
  - `Makefile`
  - **executable/**
    - `CommunityChestCard.o`
    - `MonopolyBoard.o`
    - `asset.o`
    - `color_category.o`
    - `mainImplementation.o`
    - `money.o`
    - `virtual_monopoly_board.o`


