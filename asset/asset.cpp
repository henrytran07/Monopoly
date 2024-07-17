#include "asset.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

void lower_case(string &response) {
    transform(response.begin(), response.end(), response.begin(), ::tolower);
}

// whether upgrade houses or hotels 
void Category::upgradeProperties(Properties* ptr) {
    string response;

    
    if (property.size() < maximum_property - 1 && cash >= ptr->cost_built) {
        cout << "Do you want to upgrade your house(yes/no)? ";
        cin >> response;
        lower_case(response);

        if (response == "yes") {
            int value = ptr->value;
            int rent = ptr->rent;
            int cost_built = ptr->cost_built;
            House* house = new House(value, rent, cost_built);

            property.push_back(house);
            money->chargeIt(cost_built);

            rent *= rent_base;
            value += cost_built;

            ptr->value = value;
            ptr->rent = rent;
        } else {
            // Later add step logic in
            return;
        }
    } else if (cash >= ptr->cost_built) {
        cout << "Do you want to upgrade your houses to a hotel? ";
        cin >> response;
        lower_case(response);

        if (response == "yes") {
            int rent = ptr->rent;
            int cost_built = ptr->cost_built;
            int value = ptr->value;

            for (auto pr : property) {
                delete pr;
            }

            property.clear();

            rent *= rent_base;
            money->chargeIt(cost_built);
            value += cost_built;

            Hotel* hotel = new Hotel(value, rent, cost_built);
            property.push_back(hotel);
        } else {
            // Later add step logic in
            return;
        }
    }
}

bool Asset:: search(Properties* ptr){
    string name = ptr -> name; 
    for (int player = 0; player < 4; player++){
        auto it = asset.find(player);
        if (it != asset.end()){
            auto map = it -> second; 
            auto itt = map.find(name);
            if (itt != map.end()){
                cout << "Player " << player << " owns this asset" << endl; 
                return true; 
            }
        }
    }
    return false; 
}
int Asset:: owner(Properties* ptr){
    string name = ptr -> name; 
    for (int player = 0; player < 4; player++){
        auto it = asset.find(player);
        if (it != asset.end()){
            auto map = it -> second; 
            auto itt = map.find(name);
            if (itt != map.end()){
                return player; 
            }
        }
    }
    return -1; 
}
void Asset::buyAsset(Properties* ptr, int player, const string& name) {
    string response;
    if ((cash >= ptr->value) && (!search(ptr))) {
        cout << "Do you want to acquire this asset? ";
        cin >> response;
        lower_case(response);

        if (response == "yes") {
            auto& it = asset[player];
            ptr->name = name;
            it[ptr->name] = vector<Properties*>();
            money->chargeIt(ptr->value);
        } else {
            // Later add step logic in
            return;
        }
    } else if ((cash >= ptr -> value * 2 && (search(ptr)))){
        int demanded_price; 
        cin >> response; 
        int own = owner(ptr);

        if (own != -1 && own != player){
            cout << "Player " << own << "owns it. Do you want to buy it? (yes/no) ";
            cin >> response; 
            lower_case(response);
            if (response == "yes"){
                cout << "Player " << own << "gives a price. ";
                cin >> demanded_price;

                if (cash >= demanded_price){
                    money -> chargeIt(demanded_price);
                    auto it = asset.find(own);
                    if (it != asset.end()){
                        auto& map = it -> second; 
                        auto name = map.find(ptr -> name);

                        if (name != map.end()){
                            for (const auto prop: name -> second){
                                asset[player][ptr -> name].push_back(prop);
                            }
                            name -> second.clear();
                            map.erase(name);
                        }
                    }
                    cout << "Congratulations on player " << player << endl; 
                } else {
                    cout << "Not enough to acquire this asset" << endl;
                }
            }
        }
    } else {
        cout << "You do not have enough to acquire this asset." << endl; 
        return; 
    }
}

bool Asset::bankruptcy(int player, int rent) {
    int total_net_worth = 0;
    auto it = asset.find(player);

    if (it != asset.end()) {
        for (const auto& properties : it->second) {
            for (const auto& prop : properties.second) {
                total_net_worth += prop->value;
            }
        }
    }
    return total_net_worth < rent;
}

bool Asset::checkRent(int rent) {
    return cash < rent;
}

void Asset::sellAsset(Properties* ptr, int player) {
    string response;

    auto it = asset.find(player);
    bool empty = true;

    if (it != asset.end()) {
        for (const auto& properties : it->second) {
            if (!properties.second.empty()) {
                empty = false;
                break;
            }
        }
    }

    if (empty) {
        cout << "You have nothing to sell" << endl;
        return;
    }

    if (checkRent(ptr->rent) && !bankruptcy(player, ptr->rent)) {
        cout << "Do you want us to help you automatic selling or you want to do it manually (a or b)? ";
        cin >> response;
        lower_case(response);

        if (response == "a") {
            automaticSelling(ptr->rent, player);
            money->chargeIt(ptr->rent);
        } else {
            string name;
            cout << "Your properties have names: ";

            auto it = asset.find(player);
            if (it != asset.end()) {
                for (const auto& properties : it->second) {
                    for (const auto& prop : properties.second) {
                        cout << prop->name << " ";
                    }
                }
                cout << endl;

                cout << "Please choose your option for selling: ";
                cin >> name;
                // manualSelling(name); // Uncomment this if manualSelling is implemented
            }
        }
    }
}

void Asset::automaticSelling(int rent, int player) {
    auto it = asset.find(player);
    if (checkRent(rent)) {
        for (auto& properties : it->second) {
            while (!properties.second.empty() && checkRent(rent)) {
                Properties* test = properties.second.back();
                properties.second.pop_back();
                cout << "Selling property named " << test->name << " worth " << test->value << endl;
                money->sellIt(test->value);
                delete test;
            }
            if (checkRent(rent)) {
                automaticSelling(rent, player);
            }
        }
    }
}
