#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include <iostream> 
// #include "color_category.h"
#include <vector> 
using namespace std; 

class UserBoard {
    private: 
        const int COL = 7; 
        const int ROW = 7; 
        
        void board_at_0_i_inputFile(vector<string>& board_at_0_i);
        void board_at_i_9_inputFile(vector<string>& board_at_i_9);
        void board_at_9_i_inputFile(vector<string>& board_at_9_i);
        void board_at_i_0_inputFile(vector<string>& board_at_i_0);
        vector<vector<string>> user_board();
    public:     
        void printBoard();
};

#endif 