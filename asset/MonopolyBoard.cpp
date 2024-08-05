#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // For std::setw
using namespace std;

struct UserBoard {
    static const int COL = 10; 
    static const int ROW = 10; 
    void board_at_0_i_inputFile(vector<string>& board_at_0_i);
    void board_at_i_9_inputFile(vector<string>& board_at_i_9);
    void board_at_9_i_inputFile(vector<string>& board_at_9_i);
    void board_at_i_0_inputFile(vector<string>& board_at_i_0);
    vector<vector<string>> user_board();
    void printBoard();
};

void UserBoard::board_at_0_i_inputFile(vector<string>& board_at_0_i) {
    ifstream inputFile("board_at_0_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_0_i.txt" << endl;
        return;
    }
    int index = 0;
    while (index < board_at_0_i.size() && getline(inputFile, board_at_0_i[index])) {
        index++;
    }
    inputFile.close();
}

void UserBoard::board_at_i_9_inputFile(vector<string>& board_at_i_9) {
    ifstream inputFile("board_at_i_9.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_9.txt" << endl;
        return;
    }
    int index = 0;
    while (index < board_at_i_9.size() && getline(inputFile, board_at_i_9[index])) {
        index++;
    }
    inputFile.close();
}

void UserBoard::board_at_9_i_inputFile(vector<string>& board_at_9_i) {
    ifstream inputFile("board_at_9_i.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_9_i.txt" << endl;
        return;
    }
    int index = 0;
    while (index < board_at_9_i.size() && getline(inputFile, board_at_9_i[index])) {
        index++;
    }
    inputFile.close();
}

void UserBoard::board_at_i_0_inputFile(vector<string>& board_at_i_0) {
    ifstream inputFile("board_at_i_0.txt");
    if (!inputFile.is_open()) {
        cerr << "No file found: board_at_i_0.txt" << endl;
        return;
    }
    int index = 0;
    while (index < board_at_i_0.size() && getline(inputFile, board_at_i_0[index])) {
        index++;
    }
    inputFile.close();
}

vector<vector<string>> UserBoard::user_board() {
    vector<vector<string>> user_monopoly_board(ROW, vector<string>(COL, "Empty")); // Initialize with "Empty"
    vector<string> street(COL); // Temporary storage for reading data

    board_at_0_i_inputFile(street);
    for (int col = 0; col < COL; col++) {
        user_monopoly_board[0][col] = street[col];
    }

    board_at_i_9_inputFile(street);
    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][9] = street[row];
    }

    board_at_9_i_inputFile(street);
    for (int col = 0; col < COL; col++) {
        user_monopoly_board[9][col] = street[col];
    }

    board_at_i_0_inputFile(street);
    for (int row = 0; row < ROW; row++) {
        user_monopoly_board[row][0] = street[row];
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

int main() {
    UserBoard userboard;
    userboard.printBoard();
    return 0;
}
