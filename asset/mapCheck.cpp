#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

// Mock implementations for testing purposes
class Money {
public:
    int getCash(int player) { return 1000; }
    void chargeIt(int player, int amount) { cout << "Charged player " << player << " $" << amount << endl; }
    void sellIt(int player, int amount) { cout << "Paid player " << player << " $" << amount << endl; }
};

class Color {
public:
    string getStreetName() { return "Test Street"; }
    int getPrice() { return 200; }
    int getRent() { return 50; }
    int getCostBuilt() { return 100; }
    tuple<int, int, int> color_information(map<vector<Color*>, map<string, tuple<int, int, int>>>&, const string&) { return make_tuple(200, 0, 0); }
    void priceAdjustment(int newPrice) { cout << "New price: $" << newPrice << endl; }
    void rentAdjustment(int newRent) { cout << "New rent: $" << newRent << endl; }
    void costBuiltAdjustment(int newCost) { cout << "New cost built: $" << newCost << endl; }
    map<vector<Color*>, map<string, tuple<int, int, int>>> colorMap() { return {}; }
};

class Properties {
public:
    Properties(const string&, int, int, int) {}
};

class House : public Properties {
public:
    House(const string& name, int value, int rent, int cost) : Properties(name, value, rent, cost) {}
};

class Asset {
protected:
    Money* money = new Money();
    Color* color = new Color();
    map<int, map<Color*, vector<Properties*>>> asset;
    map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

    void userHandleResponse(string &response){
        while (response != "yes" && response != "no"){
            cout << "Your response is neither yes nor no. Could you choose your option again? ";
            cin >> response;
            lower_case(response);
        }
    }

    void lower_case(string& response){
        transform(response.begin(), response.end(), response.begin(), ::tolower);
        userHandleResponse(response);
    }

    bool ownerVerification(Color* street, int player) {
        if (street == nullptr) return false;

        cout << "Printing map contents:" << endl;
        for (const auto& pair : asset) {
            cout << "Player ID: " << pair.first << endl;
            for (const auto& streetEntry : pair.second) {
                cout << "  Street Address: " << streetEntry.first << endl;
            }
        }

        auto mapIt = asset.find(player);
        if (mapIt == asset.end()) {
            cout << "Player not found: " << player << endl;
            return false;
        } else {
            cout << "Player found: " << player << endl;
        }

        auto& innerMap = mapIt->second;
        auto streetIt = innerMap.find(street);
        if (streetIt != innerMap.end()) {
            return true;
        }

        return false;
    }

    bool search(Color* street){
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

    int Owner(Color* street){
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
public:
    Asset(Money* m, Color* c) : money(m), color(c) {
        if (color != nullptr) {
            myMap = color -> colorMap();
            getAsset();
        } else {
            cerr << "Color object is null!" << endl;
        }
    }

    void printAsset(){
        for (const auto player : asset){
            cout << "player " << player.first << ": ";
            for (const auto city: player.second){
                cout << "The city name: " << city.first->getStreetName() << endl;
            }
            cout << endl;
        }
    }

    map<int, map<Color*, vector<Properties*>>> getAsset() { return asset; }

    void buyAsset(Color* street, int player){
        if (street == nullptr || color == nullptr) {
            cerr << "Invalid pointer!" << endl;
            return;
        }

        string response;
        tuple<int, int, int> colorIn = color -> color_information(myMap, street -> getStreetName());
        int value = get<0> (colorIn);

        if (!ownerVerification(street, player) && search(street)){
            cout << value << endl;

            if (money -> getCash(player) >= value){
                cout << "Player " << player << ": Do you want to acquire this asset on "
                    << street -> getStreetName() << " street having the value of $"
                    << value << "? ";
                getline(cin, response);
                lower_case(response);

                if (response == "yes"){
                    money -> chargeIt(player, value);
                    asset[player][street] = vector<Properties*>();
                } else {
                    cout << "Player " << player << " chose not to buy" << endl;
                }
            } else {
                cout << "Player " << player << " does not have enough money to buy this asset." << endl;
            }
        } else if (!search(street) && !ownerVerification(street, player)){
            value *= 2;
            int own = Owner(street);
            if (money -> getCash(player) >= value && own != -1){
                cout << "Player " << player << ": Do you want to acquire this asset on "
                    << street -> getStreetName() << " street from player " << own << " which cost you $"
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
                }
            } else {
                cout << "Not enough to acquire this asset " << endl;
            }
        } else {
            cout << "You do not have enough to acquire this asset" << endl;
        }
    }

    int netWorth(int player){
        auto properties = asset.find(player);
        int total_properties = 0;
        if (properties != asset.end()){
            auto &map = properties -> second;
            for (auto itr = map.begin(); itr != map.end(); itr++){
                Color* asst = itr -> first;
                total_properties += asst -> getPrice();
            }
        }
        int total_asset = money -> getCash(player) + total_properties;
        return total_asset;
    }

    bool bankruptcy(Color* color, int player){
        int total_asset = netWorth(player);
        if (total_asset < color -> getRent()){
            cout << "You are bankrupt." << endl;
            return true;
        }
        return false;
    }

    void eraseAsset(Color* color){
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

    void cashDeduction(Money* money, int &amount_due, int player, int owner, int sellingAsset){
        cout << amount_due << ": amount due " << endl;
        money -> sellIt(player, sellingAsset);

        if (money -> getCash(player) >= amount_due) {
            money -> chargeIt(player, amount_due);
            cout << money -> getCash(player) << ": getCash(player) " << endl;
            money -> sellIt(owner, amount_due);
            cout << money -> getCash(owner) << ": getCash(owner)" << endl;

            amount_due = 0;
            cout << amount_due << ": amount_due" << endl;
        }
    }

    void automaticSelling(int rent, int player, int owner){
        if (rent <= 0) {
            cout << rent << ": rent value in if-statement" << endl;
            money -> sellIt(player, -rent);
            rent = 0;
            return;
        }
        auto findCheapestProperties = [&] (int play) -> Color*{
            auto map = asset.find(play);
            if (map != asset.end()){
                auto& it = map -> second;
                for (auto itr = it.begin(); itr != it.end(); itr++){
                    Color* c = itr -> first;
                    int price = c -> getPrice();
                    if (price >= rent) return c;
                }
            }
            return nullptr;
        };

        while (rent > 0){
            Color* cheap_property = findCheapestProperties(player);
            if (cheap_property != nullptr){
                int sellingAsset = cheap_property -> getPrice();
                eraseAsset(cheap_property);
                rent -= sellingAsset;
                cashDeduction(money, rent, player, owner, sellingAsset);
            } else {
                cout << "Player " << player << " does not have enough property to sell" << endl;
                break;
            }
        }
    }

    void sellAsset(Color* street, int player){
        if (street == nullptr) {
            cerr << "Invalid Color pointer!" << endl;
            return;
        }

        if (!ownerVerification(street, player)){
            cout << "You do not own this asset." << endl;
            return;
        }

        cout << "Selling property at: " << street -> getStreetName() << endl;
        auto properties = asset[player].find(street);
        if (properties != asset[player].end()){
            int cost = street -> getPrice() / 2;
            asset[player].erase(properties);
            money -> sellIt(player, cost);
            cout << "Sold property for: $" << cost << endl;
        } else {
            cout << "No properties found at the given address." << endl;
        }
    }
};

class Upgrade: public Asset {
    Asset* asset;
public:
    Upgrade(Asset* a) : asset(a) {}

    void upgradeProperties(Color* color, int player){
        if (color == nullptr) {
            cerr << "Invalid Color pointer!" << endl;
            return;
        }

        if (!asset -> ownerVerification(color, player)){
            cout << "You do not own this property." << endl;
            return;
        }

        cout << "Upgrading property on: " << color -> getStreetName() << endl;
        int costBuilt = color -> getCostBuilt();
        if (asset -> netWorth(player) >= costBuilt){
            cout << "Upgrading property for $" << costBuilt << endl;
            color -> costBuiltAdjustment(costBuilt);
            asset -> eraseAsset(color);
        } else {
            cout << "Not enough funds to upgrade." << endl;
        }
    }
};

int main() {
    Money money;
    Color color;
    Asset asset(&money, &color);

    // Testing Asset methods
    asset.printAsset();

    // Simulate buying an asset
    Color street;
    asset.buyAsset(&street, 1);

    // Test the owner verification
    // bool owner = asset.ownerVerification(&street, 1);
    // cout << "Owner verification: " << (owner ? "True" : "False") << endl;

    // Test the net worth calculation
    int netWorth = asset.netWorth(1);
    cout << "Net worth: $" << netWorth << endl;

    // Simulate selling an asset
    asset.sellAsset(&street, 1);

    // Testing Upgrade class
    Upgrade upgrade(&asset);
    upgrade.upgradeProperties(&color, 1);

    return 0;
}
 