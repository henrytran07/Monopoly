#include <iostream> 
#include <map> 
#include "../money/money.h"
#include "../assetFile/asset.h"
using namespace std; 

void Money:: updatedNameMap(map<int, string> &name){
    playerName = name; 
}

void Money::cashDeclaration(){
    for (int player = 1; player <= 6; player++){
        cash[player] = 1500; 
    }

    if (cash.empty()){
        cout << "Empty cash map" << endl; 
    }
}

void Money:: chargeIt(int player, int cost){
    cout << playerName[player] << " is getting charged $" << cost << "..." << endl;
    cash[player] -= cost; 
}

void Money:: sellIt(int player, int value){
    cout << playerName[player] << " is receiving $" << value << "..." << endl; 
    cash[player] += value; 
}

// double Money:: payTax(int player){
//     map<int, map<Color*, vector<Properties*>>> asst = asset -> getAsset();
//     int total_asset = 0; 
//     auto map = asst.find(player);
//     if (map != asst.end()){
//         for (const auto& prop: map -> second){
//             total_asset+= prop.first -> getPrice();
//         }
//     }
//     double tax = tax_rate * total_asset;
//     cash[player] -= static_cast<int>(tax);
//     return tax; 
// }

void Money:: passGo(int player){
    cout << endl; 
    cout << playerName[player] << " passes Go" << endl; 
    sellIt(player, 200);
}

void Money:: printMoneyMap(){
    for (auto itr : cash){
        cout << "Player " << playerName[itr.first] << ": ";
            cout << itr.second << endl;  
    }
}
void Money:: eraseMap(int player){
    cash.erase(player);
}