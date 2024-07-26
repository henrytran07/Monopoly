#include "asset.h"
#include "color_category.h"
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <tuple> 
using namespace std; 

void lower_case(string &response){
    transform(response.begin(), response.end(), response.begin(), ::tolower);
}

tuple<int, int, int> Asset::colorInfo(Color* street) const {
    Color* color; 
    map<vector<Color*>, map<string, tuple<int, int, int>>>myMap = color -> Map();
    tuple<int, int, int> colorInformation = color -> color_information(myMap, street -> getStreetName());
    return colorInformation; 
}
bool Asset::ownerVerification(Color* street, int player){ 
    bool own = false; 
    auto checkOwner = [&](int play){
        auto map = asset.find(play);
        if (map != asset.end()){
            auto property = map -> second; 
            auto it = property.find(street);

            if (it != property.end()){
                if (play == player){
                    own = true;  
                }
                return own; 
            }
        }
        return false; 
    };
    for (int play = 1; play <= 4; play++){
        if (checkOwner(play)){
            return own; 
        }
    }
    return false; 
}

bool Asset::search(Color* street){
    auto checkStreetPresence = [&] (int player){
        auto map = asset.find(player);
        if (map != asset.end()){
            auto properties = map -> second; 
            auto it = properties.find(street);
            if (it != properties.end()){
                return true; 
            }
        }
        return false; 
    };
    for (int play = 1; play <= 4; play++){
        if (checkStreetPresence(play)){
            return false; 
        }
    }
    return true; 
}

int Asset:: Owner(Color* street){
    for (int play = 1; play <= 4; play++){
        auto map = asset.find(play);
        if (map != asset.end()){
            auto it = map -> second; 
            auto itt = it.find(street);

            if (itt != it.end()){
                return play;
            }
        }
    }
    return -1; 
}
void Asset:: eraseAsset(Color* color){
    int owner = Owner(color);
    auto map = asset.find(owner);

    if (map != asset.end()){
        auto& it = map -> second; 
        auto properties = it.find(color);
        if (properties != it.end()){
            properties -> second.clear();
            it.erase(properties);
        }
    }
}
void Asset:: buyAsset(Color* street, int player) {
    string response; 

    tuple<int, int, int> colorIn = colorInfo(street);
    int value = get<0>(colorIn);
    if ((search(street))){
        if ((money -> getCash(player) >= value)){
            cout << "Do you want to acquire this asset? ";
            getline(cin, response);
            lower_case(response);
            if (response == "yes"){
                money -> chargeIt(player, value);
                auto map = asset[player];
                map[street] = vector<Properties*>();
            } else {
                cout << "Player " << player << "chose not to buy" << endl; 
            }
        }
    } else if ((!search(street))){
        if (ownerVerification(street, player)){
            value *= 2; 
            int own = Owner(street);
            if ((money -> getCash(player) >= value) && (own!= -1)){
                cout << "Do you want to acquire this asset?";
                getline(cin, response);
                lower_case(response);
                if (response == "yes"){
                    money -> chargeIt(player, value);
                    money -> sellIt(own, value);
                    auto old_owner = asset.find(own);
                    if (old_owner != asset.end()){
                        auto &map = old_owner -> second; 
                        auto old_properties = map.find(street);

                        if (old_properties != map.end()){
                            asset[player][street] = old_properties -> second; 
                            old_properties -> second.clear();
                            map.erase(old_properties);
                        }
                    }
                    cout << "Congratulations on player " << player << endl; 
                }
            } else {
                cout << "Not enough to acquire this asset" << endl;
            }
        }
    } else {
        cout << "You do not have enough to acquire this asset" << endl; 
    }
  
}

int Asset::netWorth(int player){
    auto properties = asset.find(player);
    int total_properties = 0; 
    if (properties != asset.end()){
        auto& map = properties -> second; 
        for (auto itr = map.begin(); itr != map.end(); itr++){
            Color* asst = itr -> first; 
            total_properties += asst -> getPrice();
        }
    }
    int total_asset = money -> getCash(player) + total_properties;
    return total_asset;
}
bool Asset::bankcruptcy(Color* color, int player){
    int total_asset = netWorth(player); 
    if (total_asset < color -> getRent()){
        cout << "You are bankcrupt" << endl; 
        return true; 
    }
    
    return false; 
}

void Asset::automaticSelling(int rent, int player, int owner){
    if (rent <= 0) {return;}
    auto findCheapestProperties = [&] (int play) -> Color*{
        auto map = asset.find(play);
        if (map != asset.end()){
            auto &properties = map -> second;
            auto it = properties.begin();
            Color* cheapest = it -> first;  
            for (auto itr = properties.begin(); itr != properties.end(); itr++){
                Color* asst = itr -> first; 
                if (cheapest -> getPrice() > asst -> getPrice()){
                    cheapest = asst; 
                }
            }
            return cheapest; 
        }
        return nullptr;
    };
    
    Color* cheapest = findCheapestProperties(player);
    int value = cheapest -> getPrice();
    money->sellIt(player, value);
    money -> chargeIt(player, rent);
    money -> sellIt(owner, rent);
    rent -= money -> getCash(player);
    eraseAsset(cheapest);
       
    automaticSelling(rent, player, owner);
    
}

void Asset::manualSelling(int rent, int player, int owner){
    if (rent <= 0) {return;}

    string response; 
    auto map = asset.find(player);
    if (map != asset.end()){
        auto& it = map -> second; 

        for (auto itr = it.begin(); itr != it.end(); itr++){
            Color* color = itr -> first; 
            string street_name = color -> getStreetName();
            cout << "Your asset contains " << street_name << " with the value of $";
            cout << color -> getPrice() << endl; 

            cout << "Do you want to sell this asset? ";
            cin >> response; 
            lower_case(response);

            if (response == "yes"){
                int value = color -> getPrice();
                money -> sellIt(player, value);
                money -> chargeIt(player, rent);
                money -> sellIt(owner, rent);
                rent -= money -> getCash(player);
                eraseAsset(color);
            }
        }
    }
    manualSelling(rent, player, owner);
}
void cashDeduction(int cash, int rent, int player, int owner){
    Money* money; 
    rent -= cash; 
    money -> chargeIt(player, cash);
    money -> sellIt(owner, cash);
}
void Asset::sellAsset(Color* color, int player){
    string response; 
    int rent = color -> getRent();
    int cash = money -> getCash(player);
    int own = Owner(color);
    if (rent > cash){
        if ((!bankcruptcy(color, player))){
            cout << "Your cash is less than your rent. Do you want to manually sell your assets or ";
            cout << " you want us to automatically sell for you? (a or b) ";
            getline(cin, response); 
            if (response == "a"){
                // manual selling function 
                cashDeduction(cash, rent, player, own);
                manualSelling(rent, player, own);
            } else if (response == "b"){
                // automatic selling function
                cashDeduction(cash, rent, player, own);
                automaticSelling(rent, player, own);
            }
        }
    } else {
        cout << "Charging $" << rent << " on rent" << endl; 
        money -> chargeIt(player, rent);
        money -> sellIt(own, rent);
    }
}

void Asset::printAsset() const {
    for (const auto& playerAsset: asset){
        cout << "Player " << playerAsset.first << ": "; 
        for (const auto& colorProperties: playerAsset.second){
            cout << "Street: " << colorProperties.first -> getStreetName() << endl; 
            cout << "  Price: " << colorProperties.first -> getPrice() << endl; 
            cout << "   Rent: " << colorProperties.first -> getRent() << endl;  
        }
    }
}