#ifndef VIRTUAL_MONOPOLY_BOARD_H
#define VIRTUAL_MONOPOLY_BOARD_H

#include <iostream> 
#include <vector> 
#include <random> 
#include <numeric> 
#include "money.h"
#include "color_category.h"
#include "asset.h"
#include <tuple> 
using namespace std; 

class Virtual_Monopoly_Board{
    private: 
        Money* money; 
        Color* color; 
        vector<vector<Color*>> city; 
        vector<string> city_names;
        int player; 
        static random_device rd; 
        static mt19937 gen; 
        map<int, int> positionMap;
        int position = positionMap.at(player);
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap = color -> Map();
        
        bool diceCheck(int player);
        int throwingDice();
        bool jailCheck(string& cities);
        void stepMove(int player);
        int random_number(int begin, int end);
        string correspondingCityName(int player);
        void positionDeclaration(); 
        void city_name();
    public: 
        void initializePosition(int player){
            position = 0; 
        }
        void throwDiceForStep(int player);  
        void printBoard(int player);  
};
#endif 