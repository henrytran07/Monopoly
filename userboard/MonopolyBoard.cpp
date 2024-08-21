
#include "../userboard/MonopolyBoard.h"
#include <fstream> 
#include <iostream> 
using namespace std;

void UserBoard::board_at_0_i_inputFile(vector<string>& board_at_0_i) {
    ifstream inputFile("userboard/board_at_0_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_0_i.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        board_at_0_i.push_back(line);
    }

    if (board_at_0_i.empty()){
        cout <<"Empty vector (board_at_0_i). Needed to check the program..." << endl; 
    }
    inputFile.close();
}

void UserBoard::board_at_i_9_inputFile(vector<string>& board_at_i_9) {
    ifstream inputFile("userboard/board_at_i_9.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_9.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
       board_at_i_9.push_back(line);
    }

    if (board_at_i_9.empty()){
        cout << "Empty vector(board_at_i_9). Needed to check the program..." << endl; 
    }
    inputFile.close();
}

void UserBoard::board_at_9_i_inputFile(vector<string>& board_at_9_i) {
    ifstream inputFile("userboard/board_at_9_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_9_i.txt" << endl;
        return;
    }
    string line; 
    while (getline(inputFile, line)) {
        board_at_9_i.push_back(line);
    }

    if (board_at_9_i.empty()){
        cout << "Empty vector(board_at_9_i). Needed to check the program..." << endl; 
    }
    inputFile.close();
}

void UserBoard::board_at_i_0_inputFile(vector<string>& board_at_i_0) {
    ifstream inputFile("userboard/board_at_i_0.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_0.txt" << endl;
        return;
    }   
    string line; 
    while (getline(inputFile, line)) {
        board_at_i_0.push_back(line);
    }

    if (board_at_i_0.empty()){
        cout << "Empty vector (board_at_i_0). Needed to check the program..." << endl;
    }
    inputFile.close();
}

vector<vector<string>> UserBoard::user_board() {
    vector<vector<string>> user_monopoly_board(ROW, vector<string>(COL, "")); // Initialize with "Empty"
    vector<string> street; // Temporary storage for reading data

    board_at_0_i_inputFile(street);
    if (street.empty()){
        cout << "Empty vector named street. Needed to check the program..." << endl; 
    }
    for (int col = 0; col < COL; col++) {
        user_monopoly_board[0][col] = street[col];
        if (user_monopoly_board[0][col].empty()){
            cout << "Empty element " << "row: 0"  <<  ", col: " << col << endl; 
        }
    }

    street.clear();
    board_at_i_9_inputFile(street);

    if (street.empty()){
        cout << "Empty vector named street. Needed to check the program..." << endl; 
    }

    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][0] = street[row];
        if (user_monopoly_board[row][0].empty()){
            cout << "Empty element " << "row: " << row << ", col: 0" << endl; 
        }
    }

    street.clear();
    board_at_9_i_inputFile(street);

    if (street.empty()){
        cout << "Empty vector named street. Needed to check the program..." << endl; 
    }

    for (int col = 0; col < COL; col++) {
        user_monopoly_board[6][col] = street[col];
        if (user_monopoly_board[6][col].empty()){
            cout << "Empty element " << "row: 6" << ", col: " << col << endl; 
        }
    }

    street.clear();
    board_at_i_0_inputFile(street);
    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][6] = street[row];
        if (user_monopoly_board[row][6].empty()){
            cout << "Empty element " << "row: " << row << ", col: 6 " << endl;
        }
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


