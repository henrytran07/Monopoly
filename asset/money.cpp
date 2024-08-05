
#include "money.h"
#include <iostream> 
#include <map> 
#include "asset.h"
using namespace std; 

void Money::cashDeclaration(){
    for (int i = 1; i <= 4; i++){
        cash[i] = 1500; 
    }
}

void Money:: chargeIt(int player, int cost){
    cash[player] -= cost; 
}

void Money:: sellIt(int player, int value){
    cash[player] += value; 
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
    cash[player] -= static_cast<int>(tax);
    return tax; 
}

void Money:: passGo(int player){
    sellIt(player, 200);
}