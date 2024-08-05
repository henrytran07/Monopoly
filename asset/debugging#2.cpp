#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Forward declarations for needed classes
class Color;
class Money;
class Asset;

// Base class for properties
class Color {
public:
    Color(string nm, int val, int r, int cost) : street_name(nm), price(val), rent(r), cost_built(cost) {}
    string getStreetName() const { return street_name; }
    int getPrice() const { return price; }
    int getRent() const { return rent; }
    int getCostBuilt() const { return cost_built; }
    void priceAdjustment(int new_price) { price = new_price; }
    void rentAdjustment(int new_rent) { rent = new_rent; }
private:
    string street_name;
    int price;
    int rent;
    int cost_built;
};

// Base class for properties
class Properties : public Color {
public:
    Properties(string nm, int val, int r, int cost) : Color(nm, val, r, cost) {}
    virtual void display() const = 0;
    virtual ~Properties() = default;
};

class House : public Properties {
public:
    House(string nm, int val, int r, int cost) : Properties(nm, val, r, cost) {}
    void display() const override {
        cout << "House on the streetname " << getStreetName() << ": Value $" << getPrice() << ", Rent $" << getRent() << endl;
    }
};

class Hotel : public Properties {
public:
    Hotel(string nm, int val, int r, int cost) : Properties(nm, val, r, cost) {}
    void display() const override {
        cout << "Hotel on the streetname " << getStreetName() << ": Value $" << getPrice() << ", Rent $" << getRent() << endl;
    }
};

class Asset {
public:
    map<int, map<Color*, vector<Properties*>>>& getAsset() { return asset_map; }
    void printAsset() const;
    void mapUpdate(const map<int, map<Color*, vector<Properties*>>> &myMap);
private:
    map<int, map<Color*, vector<Properties*>>> asset_map;
};

void Asset::printAsset() const {
    for (const auto& playerAsset : asset_map) {
        cout << "Player " << playerAsset.first << ":" << endl;
        for (const auto& colorProperties : playerAsset.second) {
            cout << "  Street: " << colorProperties.first->getStreetName() << endl;
            cout << "    Price: " << colorProperties.first->getPrice() << endl;
            cout << "    Rent: " << colorProperties.first->getRent() << endl;
            for (const auto& prop : colorProperties.second) {
                prop->display();
            }
        }
    }
}

void Asset::mapUpdate(const map<int, map<Color*, vector<Properties*>>> &myMap) {
    asset_map = myMap;
}

class Money {
public:
    void chargeIt(int player, int amount) {
        cout << "Charging player " << player << " $" << amount << endl;
    }
    int getCash(int player) const { return 1000; } // Dummy value
};

void printMap(const map<int, map<Color*, vector<Properties*>>>& myMap) {
    for (const auto& playerAsset : myMap) {
        cout << "Player " << playerAsset.first << ":" << endl;
        for (const auto& colorProperties : playerAsset.second) {
            cout << "  Street: " << colorProperties.first->getStreetName() << endl;
            cout << "    Price: " << colorProperties.first->getPrice() << endl;
            cout << "    Rent: " << colorProperties.first->getRent() << endl;
        }
    }
}

class Upgrade {
public:
    Money* money = nullptr;
    int maximum_properties_size = 4;
    vector<Properties*> properties;
    Asset* asset = nullptr;
    static const int rent_rate = 2;
    static const int value_rate = 2;

    void houseUpgrade(Color* color, int player);
    void hotelUpgrade(Color* color, int player);
    void valueAdjustment(Color* color, int player);
    void upgradeProperties(Color* color, int player);
    void print() const; // Declaration of the print function
    void upgradeProperties(const vector<Properties*>& prop);
};

void Upgrade:: upgradeProperties(const vector<Properties*>& prop){
    properties = prop; 
}
void lower_case(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

bool ownerVerification(Color* color, int player) {
    return true; // Dummy value
}

void buyAsset(Color* color, int player) {
    cout << "Buying asset for player " << player << endl;
}

void addProperties(map<int, map<Color*, vector<Properties*>>>& myMap, Color* color, int player, Money* money, Asset* asset, Upgrade* upgrade) {
    auto map = myMap.find(player);
    if (map != myMap.end()) {
        auto it = map->second.find(color);
        if (it != map->second.end()) {
            vector<Properties*>& properties = it->second;
            // cout << properties.size() << ": vector's size" << endl; 

            int value = color->getPrice();
            int rent = color->getRent();
            int cost_built = color->getCostBuilt();

            if (properties.size() < 4) {
                money->chargeIt(player, cost_built);
                properties.push_back(new House(color->getStreetName(), value, rent, cost_built));

                upgrade -> upgradeProperties(properties);
                myMap[player][color] = properties;
                asset->mapUpdate(myMap);
                cout << endl; 
            } else {
                money->chargeIt(player, cost_built);
                properties.clear();
                properties.push_back(new Hotel(color->getStreetName(), value, rent, cost_built));
                 upgrade -> upgradeProperties(properties);
                myMap[player][color] = properties;
                asset->mapUpdate(myMap);
               
            }
        }
    }
}

void Upgrade::houseUpgrade(Color* color, int player) {
    string response;
    int cost_built = color->getCostBuilt();
 
    map<int, map<Color*, vector<Properties*>>> myMap = asset->getAsset();
    cout << properties.size() << ": vector's size" << endl; 
    cout << "Do you want to upgrade your asset to ";
    cout << (properties.size() + 1 == 1 ? "a house" : to_string(properties.size() + 1) + " houses") << "? " << endl;
    cin >> response;
    lower_case(response);

    if (response == "yes") { 
        addProperties(myMap, color, player, money, asset, this);
    }
}

void Upgrade::hotelUpgrade(Color* color, int player) {
    string response;
    map<int, map<Color*, vector<Properties*>>> myMap = asset->getAsset();
    cout << "Do you want to upgrade your asset to hotel? ";
    cin >> response;
    lower_case(response);

    if (response == "yes") {
        addProperties(myMap, color, player, money, asset, this);
    }
}

void Upgrade::valueAdjustment(Color* color, int player) {
    int value = color->getPrice();
    int rent = color->getRent();
    value *= value_rate;
    rent *= rent_rate;
    color->priceAdjustment(value);
    color->rentAdjustment(rent);
}

void Upgrade::upgradeProperties(Color* color, int player) {
    int cost_built = color->getCostBuilt();
    int cash = money->getCash(player);
  
    if (ownerVerification(color, player)) {
        if (cash >= cost_built) {
            if (properties.size() != maximum_properties_size) {
                houseUpgrade(color, player);
                valueAdjustment(color, player);
                cout << endl;
            } else {
                hotelUpgrade(color, player);
                valueAdjustment(color, player);
            }
        } else {
            cout << "You do not have enough money to update" << endl;
        }
    } else {
        buyAsset(color, player);
    }
}

void Upgrade::print() const {
    cout << "Properties upgrade details:" << endl;
    for (const auto& prop : properties) {
        prop->display();
    }
}

int main() {
    // Initialize test objects
    Color* color1 = new Color("Park Place", 350, 50, 200);
    Color* color2 = new Color("Boardwalk", 400, 60, 250);

    Money* money = new Money();
    Asset* asset = new Asset();
    
    Upgrade upgrade;
    upgrade.money = money;
    upgrade.asset = asset;

    // Add properties map
    map<int, map<Color*, vector<Properties*>>> myMap;
    myMap[1][color1] = vector<Properties*>();
    myMap[1][color2] = vector<Properties*>();
    asset->mapUpdate(myMap);

    // Test house upgrade
    cout << "Testing house upgrade:" << endl;
    upgrade.upgradeProperties(color1, 1);
    
    upgrade.upgradeProperties(color1, 1);

    // Clean up
    delete color1;
    delete color2;
    delete money;
    delete asset;

    return 0;
}
