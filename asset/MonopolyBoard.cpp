
#include "MonopolyBoard.h"
#include <fstream> 
#include <iostream> 
using namespace std;

void UserBoard::board_at_0_i_inputFile(vector<string>& board_at_0_i) {
    ifstream inputFile("board_at_0_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_0_i.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        board_at_0_i.push_back(line);
    }
    inputFile.close();
}

void UserBoard::board_at_i_9_inputFile(vector<string>& board_at_i_9) {
    ifstream inputFile("board_at_i_9.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_9.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
       board_at_i_9.push_back(line);
    }
    inputFile.close();
}

void UserBoard::board_at_9_i_inputFile(vector<string>& board_at_9_i) {
    ifstream inputFile("board_at_9_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_9_i.txt" << endl;
        return;
    }
    string line; 
    while (getline(inputFile, line)) {
        board_at_9_i.push_back(line);
    }
    inputFile.close();
}

void UserBoard::board_at_i_0_inputFile(vector<string>& board_at_i_0) {
    ifstream inputFile("board_at_i_0.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_0.txt" << endl;
        return;
    }   
    string line; 
    while (getline(inputFile, line)) {
        board_at_i_0.push_back(line);
    }
    inputFile.close();
}

vector<vector<string>> UserBoard::user_board() {
    vector<vector<string>> user_monopoly_board(ROW, vector<string>(COL, "")); // Initialize with "Empty"
    vector<string> street(COL); // Temporary storage for reading data

    board_at_0_i_inputFile(street);
    for (int col = 0; col < COL; col++) {
        user_monopoly_board[0][col] = street[col];
        cout << user_monopoly_board[0][col] << " ";
    }
    cout << endl; 

    board_at_i_9_inputFile(street);
    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][0] = street[row];
    }

    board_at_9_i_inputFile(street);
    for (int col = 0; col < COL; col++) {
        user_monopoly_board[6][col] = street[col];
    }

    board_at_i_0_inputFile(street);
    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][6] = street[row];
    }

    return user_monopoly_board;
}

void UserBoard::printBoard() {
    vector<vector<string>> user = user_board();
    
    // Define width for each column
    const int width = 15; // Adjust width as needed
    
    // Print the board with borders
    for (int row = 0; row < ROW; row++) {
        // Print top border
        if (row == 0) {
            cout << "+";
            for (int col = 0; col < COL; col++) {
                cout << string(width, '-') << "+";
            }
            cout << endl;
        }

        // Print board row
        cout << "|";
        for (int col = 0; col < COL; col++) {
            cout << setw(width) << user[row][col] << "|";
        }
        cout << endl;

        // Print bottom border of each row
        cout << "+";
        for (int col = 0; col < COL; col++) {
            cout << string(width, '-') << "+";
        }
        cout << endl;
    }
}


