
#include "properties.h"
#include <iostream> 
using namespace std; 


bool financialQualification(int value, int cash){
    if (value < cash)
        return true; 
    return false; 
}

void Upgrade:: updateVector(const vector<Properties*> &prop){
    properties = prop; 
}

void Upgrade:: addProperties(map<int, map<Color*, vector<Properties*>>> &map_color, Color* color, int player, Asset* asset, Upgrade* upgrade, Money* money){
    auto map = myMap.find(player);
    string street_name = color -> getStreetName();

    int value = color -> getPrice();
    int rent = color -> getRent();
    int cost_built = color -> getCostBuilt();
    
    if (map != myMap.end()){
        auto it = map -> second; 
        auto prop = it.find(color);
        if (prop != it.end()){
            vector<Properties*> &properties = prop -> second; 
            if (properties.size() < 4){
                money -> chargeIt(player, cost_built);
                House* house = new House(street_name, value, rent, cost_built); 

                properties.push_back(house);
                upgrade -> updateVector(properties);
                myMap[player][color] = properties;
                asset -> mapUpdate(myMap);
            } else {
                money -> chargeIt(player, cost_built);
                Hotel* hotel = new Hotel(street_name, value, rent, cost_built);

                properties.clear();
                prop -> second.clear();
                properties.push_back(hotel);
                updateVector(properties);
                myMap[player][color] = properties;
                asset -> mapUpdate(myMap);
            }
            
        }
    }
}
void Upgrade:: houseUpgrade(Color* color, int player) {
    string response; 
    int cost_built = color -> getCostBuilt();
    int properties_size = properties.size();

    cout << "Do you want to upgrade your asset to " 
         << (properties_size + 1 == 1 ? " a house" :  to_string(properties_size + 1) + " houses")
        <<  " on " << color -> getStreetName() << " street, which cost you $" << cost_built << "? ";
    getline(cin, response);
    lower_case(response);
    if (response == "yes"){
        addProperties(myMap, color, player, asset, this, money);
        valueAdjustment(color, player);
    } else {
        // Logically add step in later. 
        cout << "You chose not to upgrade the house. " << endl;  
    }
}

void Upgrade:: hotelUpgrade(Color* color, int player){
    string response; 
    int cost_built = color -> getCostBuilt();
    map<int, map<Color*, vector<Properties*>>> myMap = asset -> getAsset();
    cout << "Do you want to upgrade your asset to hotel on "
        << color -> getStreetName() << " street, which cost you $"
        << cost_built << "? ";
    getline(cin, response); 
    lower_case(response);

    if (response == "yes"){
        addProperties(myMap, color, player, asset, this, money);
        valueAdjustment(color, player);
    } else {
        // Logically add step in later. 
        cout << "You chose not to upgrade the hotel on " << color -> getStreetName()
            << " street." << endl;  
    }
}

void Upgrade::valueAdjustment(Color* color, int player){
    int value = color -> getPrice();
    int rent = color -> getRent();
    int cost_built = color -> getCostBuilt();
    
    value *= value_rate;
    rent *= rent_rate;
    cost_built *= cost_built_rate;

    color -> priceAdjustment(value);
    color -> rentAdjustment(rent);
    color -> costBuiltAdjustment(cost_built);
}

void Upgrade:: upgradeProperties(Color* color, int player){
    int cost_built = color -> getCostBuilt();
    int cash = money -> getCash(player);
    if (ownerVerification(color, player)){
        if (financialQualification(cost_built, cash)){
            if (properties.size() != maximum_houses){
                houseUpgrade(color, player);
            } else {
                hotelUpgrade(color, player);
            }   
        } else {
            cout << "You do not have enough money to update" << endl; 
        }
    } else {
        cout << "You do not own this asset" << endl; 
        buyAsset(color, player);
    }  
}