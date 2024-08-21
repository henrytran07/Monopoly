
#ifndef MONEY_H
#define MONEY_H

#include <iostream> 
#include <map> 
#include "../assetFile/asset.h"

using namespace std; 
class Asset; 
class Money {
    private:  
        Asset* asset;   
        static double tax_rate;
        map<int, int> cash;
        map<int, string> playerName;
        void cashDeclaration();
    public: 
        Money(){
            cashDeclaration(); 
        }
        void static initializeValue(){
            tax_rate = 0.3; 
        };

        void updatedNameMap(map<int, string>& name);
        int getCash(int player) {return cash.at(player);}  
        void printMoneyMap();
        void chargeIt(int player, int cost);
        void sellIt(int player, int value); 
        // double payTax(int player);
        void passGo(int player);
        void eraseMap(int player);
};
#endif 