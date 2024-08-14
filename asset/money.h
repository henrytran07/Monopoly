
#ifndef MONEY_H
#define MONEY_H

#include <iostream> 
#include <map> 
#include "asset.h"
using namespace std; 

class Money {
    private:  
        Asset* asset;   
        int player; 
        static double tax_rate;
        map<int, int> cash;
        void cashDeclaration();
    public: 
        Money(){
            cashDeclaration(); 
        }
        void static initializeValue(){
            tax_rate = 0.3; 
        };
        int getCash(int player) {return cash.at(player);}  
        void chargeIt(int player, int cost);
        void sellIt(int player, int value); 
        double payTax(int player);
        void passGo(int player);
        void eraseMap(int player);
};
#endif 