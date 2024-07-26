
#include "money.h"
#include <iostream> 
#include <map> 
#include "try.h"
using namespace std; 

void Money::cashDeclaration(){
    cash[1] = 1500; 
    cash[2] = 1500; 
    cash[3] = 1500; 
    cash[4] = 1500; 
}

void Money:: chargeIt(int player, int cost){
    money -= cost; 
}

void Money:: sellIt(int player, int value){
    money += value; 
}

double Money:: payTax(int player){
    map<int, map<Color*, vector<Properties*>>> asst = asset -> getAsset();
    int total_asset = 0; 
    auto map = asst.find(player);
    if (map != asst.end()){
        for (const auto& prop: map -> second){
            total_asset+= prop.first -> getPrice();
        }
    }
    double tax = tax_rate * total_asset;
    return tax; 
}
   