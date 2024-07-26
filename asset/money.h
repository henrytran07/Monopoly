
#ifndef MONEY_H
#define MONEY_H

#include <iostream> 
#include <map> 
#include "try.h"
using namespace std; 

class Money {
    private:  
        Asset* asset;   
        int player; 
        const static double tax_rate = 0.3;
        map<int, int> cash;
        int money = cash.at(player);
        void cashDeclaration();
    public: 
        Money(int player, int initial_cash): money(initial_cash), player(player) {}
        int getCash(int player) {return money;}  
        void chargeIt(int player, int cost);
        void sellIt(int player, int value); 
        double payTax(int player);
};
#endif 