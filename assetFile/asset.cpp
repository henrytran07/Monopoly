#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <tuple> 
#include "../money/money.h"
#include "../assetFile/asset.h"
#include "../virtual_monopoly_board/virtual_monopoly_board.h"
using namespace std; 

Properties:: Properties(string nm, int val, int r, int cost): Color(nm, val, r, cost){}

House:: House(string nm, int val, int r, int cost): Properties(nm, val, r, cost) {}

void House:: display() const {
    cout << "House on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl;
}

Hotel:: Hotel(string nm, int val, int r, int cost): Properties(nm, val, r, cost) {}

void Hotel:: display() const {
    cout << "Hotel on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl; 
}

Asset:: Asset() {
    money = new Money();
    color = new Color();
}

Asset::  Asset(Money* m, Color* c): money(m), color(c) {
    if (color != nullptr) {
        myMap = color -> colorMap();
    } else {
        cerr << "Color object is null" << endl; 
    }
}
void Asset::userHandleResponse(string &response, const string& first_condition, const string& second_condition){
    transform(response.begin(), response.end(), response.begin(), ::tolower);
    userTrialInput(response, first_condition, second_condition);
}

void Asset::userTrialInput(string& response, const string& first_condition, const string& second_condition){
    while (response != first_condition && response != second_condition){
        cout << "Your response is neither yes nor no. Could you choose your option again? ";
        getline(cin, response);
        transform(response.begin(), response.end(), response.begin(), ::tolower);
    } 
}

bool Asset::ownerVerification(Color* street, int player){ 
    if (street == nullptr) return false; 

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

int Asset:: findOwner(Color* street){
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

void Asset:: updatedNameMap(map<int, string>& mapName){
    playerName = mapName; 
}

map<vector<Color*>, map<string, tuple<int, int, int>>> Asset:: getMyMap(){
    return myMap; 
}

void Asset:: printAsset() {
    for (const auto player : asset){
        cout << playerName[player.first]<< ": " ; 
        // cout << "Player " << player.first << ": ";
        for (const auto city : player.second){
            cout << "The city name: " << city.first -> getStreetName() << endl; 
            cout << "  Properties'size: " << city.second.size() << endl; 
        }
        cout << endl; 
    }
}

void Asset:: buyAsset(Color* street, int player) {
    if (street == nullptr || color == nullptr) {
        cerr << "Invalid pointer! " << endl; 
        return; 
    }
    
    string name = playerName[player];
    string street_name = street -> getStreetName();
    string response;
    
    string first_condition = "yes";
    string second_condition = "no";

    if (name.empty()) {
        cout << "Needed to check on the playerName map" << endl; 
        exit(0);
    }
    int value = street -> getPrice();
    
    for (int space = 0; space < special_space.size(); space++){
        if (street -> getStreetName() == special_space[space]){
            return; 
        }
    }
    
    cout << street_name << " is estimated at $" << value << endl; 
    if ((!ownerVerification(street, player)) && (streetLookUp(street))){
        
        if (money -> getCash(player) >= value){
            cout << name << ": Do you want to acquire this asset on "
                << street_name<< " street having the value of $"
                << value << " ? ";
            getline(cin, response);
            userHandleResponse(response, first_condition, second_condition);

            if (response == first_condition){
                money -> chargeIt(player, value);
                asset[player][street] = vector<Properties*> ();
                // printAsset();
                // upgrade -> mapChange(asset);
            } else {
                cout << name << " chose not to buy this asset." << endl;
            }
        } else {
            cout << name << " does not have enough cash to buy this asset." << endl; 
        }
    } else if ((!ownerVerification(street, player)) && (!streetLookUp(street))){
        value *= 2; 
        int owner = findOwner(street);

        if (money -> getCash(player) >= value){
            cout << name << ": Do you want to acquire this asset on "
                << street_name << " street from " << playerName[owner]
                << " that costs you $" << value << "? ";
            getline(cin, response);
            userHandleResponse(response, first_condition, second_condition);

            if (response == first_condition){
                money -> chargeIt(player, value);
                money -> sellIt(owner, value);
                auto old_owner = asset.find(owner);

                if (old_owner != asset.end()){
                    auto& map = old_owner -> second; 
                    auto old_properties = map.find(street);

                    if (old_properties != map.end()){
                        vector<Properties*> properties = old_properties -> second; 
                        properties.clear();
                        map.erase(street);

                        asset[player][street] = properties; 
                        // upgrade -> mapChange(asset);
                    }
                }

                cout << playerName[player] << " is sucessfully acquiring " << street_name << " asset from " << playerName[owner] << endl; 
            }
        } else {
            cout << name << ": Not enough to acquire this asset " << endl; 
        }
    } else {
        cout << "There are something off with the program" << endl;
    }
}
int Asset::calculatingPlayerNetWorth(int player){
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
bool Asset::bankruptcy(Color* color, int player){
    int total_asset = calculatingPlayerNetWorth(player); 

    string player_name = playerName[player];
    if (findOwner(color) != -1){
        if (total_asset < color -> getRent()){
            cout << player_name << " is bankrupt..." << endl; 
            playerName.erase(player);

            return true;  
        } else {
            return false; 
        }
        
    }
    
    return false; 
}

void Asset:: eraseAsset(Color* color){
    int owner = findOwner(color);
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

void Asset::cashDeduction(Money* money, int& amount_due, int player, int owner, int sellingAsset){
    money -> sellIt(player, sellingAsset);

    if (money -> getCash(player) >= amount_due){
        money -> chargeIt(player, amount_due);
        if (owner == 0){
            // in case bailingOutAssessment in the Virtual_Monopoly_Board class.
        } else {
            money -> sellIt(owner, amount_due);
        }
        
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
    int cheapest_asset_value = cheapest -> getPrice();
    money->sellIt(player, cheapest_asset_value);
    money -> chargeIt(player, rent);
    if (owner == 0){
        // in case bailingOutAssessmment in the Virtual_Monopoly_Board class. 
    } else {
        money -> sellIt(owner, rent);
    }

    if (rent > money -> getCash(player)){
        automaticSelling(rent, player, owner);
    } else {
        money -> chargeIt(player, rent);
        rent = 0; 
    }

    eraseAsset(cheapest);   
}

void Asset::manualSelling(int rent, int player, int owner, const string& first_condition, const string& second_condition){
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
        auto &it = map -> second; 

        while(amount_due > money -> getCash(player)){
            bool assetSold = false; 

            try {
                for (auto itr = it.begin(); itr != it.end(); itr++){
                    Color* color = itr -> first; 
                    string street_name = color -> getStreetName();
                    int value = color -> getPrice();

                    cout << playerName[player] << ": ";
                    cout << "Your asset has " << street_name
                        << " with the value of $" << value << endl; 
                    
                    cout << "Do you want to sell this asset? ";
                    getline(cin, response);
                    userHandleResponse(response, first_condition, second_condition);
                    if (response == first_condition){
                        cashDeduction(money, amount_due, player, owner, value);
                        eraseAsset(color);

                        assetSold = true; 
                        if (amount_due <= money -> getCash(player)){
                            break; 
                        }
                    }

                    if ((!assetSold)){
                        throw invalid_argument("the amount due is still greater than your cash possession. ");
                    }
                }
            } catch(invalid_argument &e){
                cout << "\n You still have to sell off your asset because "
                    << e.what() << endl; 
                cout << endl;
            }
        }
    }
}

void Asset::sellAsset(Color* color, int player){
    string response; 
    int rent = color -> getRent();
    string street_name = color -> getStreetName();
    int cash = money -> getCash(player);
    int owner = findOwner(color);
    
    string first_condition = "a";
    string second_condition = "b";

    string player_name = playerName[player];

    if((!ownerVerification(color, player)) && (!streetLookUp(color))){
        cout << "The rent at " << street_name << " costs you $" << rent << endl; 
        cout << "The property is owned by " << playerName[owner] << endl; 
        cout << "Charging " << player_name << " $" <<  rent << " for rent" << endl;
        if (rent > cash){
            if ((!bankruptcy(color, player))){
                cout << "Your cash is less than your rent. Do you want us to automatically sell for you "
                    << " or you want to manually sell your asset? (a or b) ";
                getline(cin, response);
                userHandleResponse(response, first_condition, second_condition); 

                if (response == "a"){
                    automaticSelling(rent, player, owner);
                    buyAsset(color, player);
                    // upgrade -> mapChange(asset);
                } else if (response == "b"){
                    manualSelling(rent, player, owner, first_condition, second_condition);
                    buyAsset(color, player);
                    // upgrade -> mapChange(asset);
                } 
            } else {
                // Evaluate that the player is bankrupt
            }
        } else if (cash >= rent) {
            money -> chargeIt(player, rent);
            money -> sellIt(owner, rent);
            buyAsset(color, player);
            // upgrade -> mapChange(asset);
        }
    } else if (streetLookUp(color)){
        buyAsset(color, player);
        // upgrade -> mapChange(asset);
    } else {
        cout << player_name << ": ";
        cout << "This is your asset" << endl; 
    }  
}

void Asset:: playerAssetElimination(int player){
    auto outterMap = asset.find(player);

    if (outterMap != asset.end()){
        auto innerMap = outterMap -> second; 
        for (auto itr = innerMap.begin(); itr != innerMap.end(); itr++){
            itr -> second.clear();
            innerMap.erase(itr);
        }
    }   
    
    // upgrade -> mapChange(asset);
    if (outterMap != asset.end()){
        cout << "Map is deleting improperly..." << endl; 
        cout << "Needed to check asset map in Asset class" << endl; 
    }

}

void Asset::mapUpdate(map<int, map<Color*, vector<Properties*>>>& myMap){
    myMap = asset; 
}

void Asset::modifiedMap(map<int, map<Color*, vector<Properties*>>>& myMap){
    myMap = asset; 
}

Money* Asset:: getMoney(){
    return money; 
}

Color* Asset::getColor(){
    return color; 
}

Upgrade:: Upgrade(Asset* asst): Asset(asst -> getMoney(), asst -> getColor()), asst(asst){
    if (asst != nullptr){
        myMap = asst -> getAsset();
    } else {
        cout << "null pointer" << endl; 
    }
}
bool financialQualification(int value, int cash){
    if (value < cash)
        return true; 
    return false; 
}

void Upgrade:: mapChange(map<int, map<Color*, vector<Properties*>>> & asset){
    myMap = asset; 
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
                myMap[player][color] = properties;
                asset -> mapUpdate(myMap);
                properties.clear();
            } else {
                money -> chargeIt(player, cost_built);
                Hotel* hotel = new Hotel(street_name, value, rent, cost_built);

                properties.clear();
                prop -> second.clear();
                properties.push_back(hotel);
                myMap[player][color] = properties;
                asset -> mapUpdate(myMap);
                properties.clear();
            }
            
        }
    }
}
void Upgrade:: houseUpgrade(Color* color, int player, const string& first_condition, const string& second_condition) {
    string response; 

    int cost_built = color -> getCostBuilt();
    string player_name = playerName[player];

    auto outterMap = myMap.find(player);
    if (outterMap != myMap.end()){
        auto innerMap = outterMap -> second; 
        auto it = innerMap.find(color);

        if (it != innerMap.end()){
            properties = it -> second; 
        }
    }
    int properties_size = properties.size();
    properties.clear();

    cout << player_name << ": "
         << "Do you want to upgrade your asset to " 
        << (properties_size + 1 == 1 ? " a house" :  to_string(properties_size + 1) + " houses")
        <<  " on " << color -> getStreetName() << " street, which cost you $" << cost_built << "? ";
    getline(cin, response);
    userHandleResponse(response, first_condition, second_condition);

    if (response == first_condition){
        addProperties(myMap, color, player, asst, this, money);
        valueAdjustment(color, player);
        asst -> printAsset();
    } else {
        // Logically add step in later. 
        cout << "You chose not to upgrade the house. " << endl;  
    }
}

void Upgrade:: hotelUpgrade(Color* color, int player, const string& first_condition, const string& second_condition){
    string response; 
    string player_name = playerName[player];

    int cost_built = color -> getCostBuilt();

    cout << player_name << ": "
         << "Do you want to upgrade your asset to hotel on "
        << color -> getStreetName() << " street, which cost you $"
        << cost_built << "? ";
    getline(cin, response); 
    userHandleResponse(response, first_condition, second_condition);

    if (response == "yes"){
        addProperties(myMap, color, player, asst, this, money);
        valueAdjustment(color, player);
        asst -> printAsset();
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

    string first_condition = "yes";
    string second_condition = "no";

    if (ownerVerification(color, player)){
        if (financialQualification(cost_built, cash)){
            if (properties.size() != maximum_houses){
                cout << "In process of upgrading houses..." << endl; 
                houseUpgrade(color, player, first_condition, second_condition);
            } else {
                hotelUpgrade(color, player, first_condition, second_condition);
            }   
        } else {
            cout << "In process of upgrading hotel..." << endl; 
            cout << "You do not have enough money to update" << endl; 
        }
    } else {
        cout << "You do not own this asset" << endl; 
        buyAsset(color, player);
    }  
}