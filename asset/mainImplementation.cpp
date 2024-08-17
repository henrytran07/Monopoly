
#include "virtual_monopoly_board.h"
#include <iostream> 

using namespace std; 

int main(){
    Virtual_Monopoly_Board* virtual_board = new Virtual_Monopoly_Board();
    
    // virtual_board -> positionInitialization();
    virtual_board -> gameStart();
    // virtual_board -> printColorMap();
    delete virtual_board;

    return 0; 
}