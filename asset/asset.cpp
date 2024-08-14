#include "asset.h"
#include "color_category.h"
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <tuple> 
using namespace std; 

void Asset::userHandleResponse(string& response){
    while (response != "yes" || response != "no"){
        cout << "Your response is neither yes nor no. Could you choose your option again? ";
        getline(cin, response);
        lower_case(response);
    } 
}
void Asset::lower_case(string &response){
    transform(response.begin(), response.end(), response.begin(), ::tolower);
    userHandleResponse(response);
}

bool Asset::ownerVerification(Color* street, int player){ 
    if (street == nullptr) return true; 

    auto mapIt = asset.find(player);
 
    auto& innerMap = mapIt -> second; 
    auto streetIt = innerMap.find(street);
    if (streetIt != innerMap.end()){
        return true; 
    }
    return false; 
}

bool Asset::streetLookUp(Color* street){
    if (street == nullptr) return false; 

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

int Asset:: findOwnership(Color* street){
    if (street == nullptr) return -1; 
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
    int owner = findOwnership(color);
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
    if (street == nullptr || color == nullptr) {
        cerr << "Invalid pointer " << endl; 
        return; 
    }

    string response; 

    tuple<int, int, int> colorInfo  = color -> color_information(myMap, street -> getStreetName());
    int value = get<0>(colorInfo);
    
    if ((!ownerVerification(street, player))){
        if ((streetLookUp(street))){

            if (money -> getCash(player) >= value){
                cout << "Player " << player << ": Do you want to acquire this asset on "
                    << street -> getStreetName() << " street having the value of $"
                    << value << "? "; 
                getline(cin, response);
                lower_case(response);

                if (response == "yes") {
                    money -> chargeIt(player, value);
                    asset[player][street] = vector<Properties*>();
                } else {
                    cout << "Player " << player << " chose not to buy. " << endl; 
                }
            } else {
                cout << "Player " << player << " does not have enough money to acquire this asset. " << endl; 
            }
        } else if ((!streetLookUp(street))){
            value *= 2; 
            int own = findOwnership(street);
            
            if (money -> getCash(player) >= value && own != -1){
                cout << "Player " << player << ": Do you want to acquire this asset on "
                    << street -> getStreetName() << " street from the player " << own << "which cost you $"
                    << value << "? ";
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
                } else {
                    cout << "Player " << player << " chose not to buy. " << endl; 
                }
            } else {
                cout << "Player " << player << " does not have enough money to acquire this asset." << endl; 
            }
        }
  
    } else {
        cout << " There is something wrong with the program. " << endl; 
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

void Asset::cashDeduction(Money* money, int& amount_due, int player, int owner, int sellingAsset){
    money -> sellIt(player, sellingAsset);

    if (money -> getCash(player) >= amount_due){
        money -> chargeIt(player, amount_due);
        money -> sellIt(owner, amount_due);

        amount_due = 0; 
    }
}
void Asset::automaticSelling(int rent, int player, int owner){
    if (rent <= 0) {
        money -> sellIt(player, -rent);
        rent = 0;
        return;
    }
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

    if (rent > money -> getCash(player)){
        rent -= money -> getCash(player);
    } else {
        money -> chargeIt(player, rent);
        rent = 0; 
    }
    automaticSelling(rent ,player, owner);
    eraseAsset(cheapest);   
}

void Asset::manualSelling(int rent, int player, int owner){
    int cash = money -> getCash(player);
    int amount_due = rent - cash; 
    if (amount_due <= 0){
        money -> sellIt(player, -amount_due);
        amount_due = 0; 
        return; 
    }

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
            getline(cin, response);
            lower_case(response);
            userHandleResponse(response);
            if (response == "yes"){
                int value = color -> getPrice();
                cashDeduction(money, amount_due, player, owner, value);
                eraseAsset(color);

                if (amount_due > money -> getCash(player)){
                    manualSelling(rent, player, owner);
                } else {
                    break;
                }
            }
        }
    }
}

void Asset::sellAsset(Color* color, int player){
    string response; 
    int rent = color -> getRent();
    int cash = money -> getCash(player);
    int own = findOwnership(color);
  
    if((!ownerVerification(color, player))){
        if (rent > cash){
            if ((!bankcruptcy(color, player))){
                cout << "Your cash is less than your rent. Do you want us to automatically sell for you "
                    << " or you want to manually sell your asset? (a or b) ";
                getline(cin, response);

                if (response == "a"){
                    automaticSelling(rent, player, own);
                    buyAsset(color, player);
                } else if (response == "b"){
                    manualSelling(rent, player, own);
                    buyAsset(color, player);
                } 
            } else {
                cout << "You do not have enough money to pay rent" << endl; 
            }
        } else if (cash >= rent) {
            cout << "Charging player " << player << " $" << rent << " for rent" << endl; 
            money -> chargeIt(player, rent);
            money -> sellIt(own, rent);
            buyAsset(color, player);
        }
    } else {
        cout << "This is your asset" << endl; 
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

void Asset::mapUpdate(map<int, map<Color*, vector<Properties*>>>& myMap){
    myMap = asset; 
}

void Asset::modifiedMap(map<int, map<Color*, vector<Properties*>>>& myMap){
    myMap = asset; 
