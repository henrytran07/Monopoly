#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

// Utility function to convert strings to lowercase
void lower_case(string &response) {
    transform(response.begin(), response.end(), response.begin(), ::tolower);
}

// Forward declarations for classes
class Properties;
class House;
class Hotel;
class Category;
class Asset;
class Color;
class Money;

// Money class to handle cash transactions
class Money {
public:
    int cash;
    Money(int initial_cash) : cash(initial_cash) {}

    void chargeIt(int cost) {
        cash -= cost;
    }

    void sellIt(int value) {
        cash += value;
    }
};

// Color class to handle property color categories
class Color {
private:
    string street_name;
    int price, rent;
    int cost_built;

public:
    Color(string name, int p, int r, int cost) : street_name(name), price(p), rent(r), cost_built(cost) {}

    tuple<int, int, int> color() const {
        return make_tuple(price, rent, cost_built);
    }

    static vector<Color*> BROWN() {
        vector<Color*> colors;
        colors.push_back(new Color("Mediterranean Avenue", 2000, 2, 50));
        colors.push_back(new Color("Baltic Avenue", 2000, 4, 50));
        return colors;
    }

    static vector<Color*> LIGHT_BLUE() {
        vector<Color*> colors;
        colors.push_back(new Color("Oriental Avenue", 3000, 6, 50));
        colors.push_back(new Color("Vermont Avenue", 3000, 6, 50));
        colors.push_back(new Color("Connecticut Avenue", 3200, 8, 50));
        return colors;
    }

    static vector<Color*> PINK() {
        vector<Color*> colors;
        colors.push_back(new Color("St. Charles Place", 3500, 10, 100));
        colors.push_back(new Color("States Avenue", 3500, 10, 100));
        colors.push_back(new Color("Virginia Avenue", 3700, 12, 100));
        return colors;
    }

    static vector<Color*> ORANGE() {
        vector<Color*> colors;
        colors.push_back(new Color("St. James Place", 4500, 14, 100));
        colors.push_back(new Color("Tennessee Avenue", 4500, 14, 100));
        colors.push_back(new Color("New York Avenue", 4800, 16, 100));
        return colors;
    }

    static vector<Color*> RED() {
        vector<Color*> colors;
        colors.push_back(new Color("Kentucky Avenue", 2200, 18, 150));
        colors.push_back(new Color("Indiana Avenue", 2200, 18, 150));
        colors.push_back(new Color("Illinois Avenue", 2400, 20, 150));
        return colors;
    }

    static vector<Color*> YELLOW() {
        vector<Color*> colors;
        colors.push_back(new Color("Atlantic Avenue", 6000, 26, 150));
        colors.push_back(new Color("Ventnor Avenue", 6000, 26, 150));
        colors.push_back(new Color("Marvin Gardens", 6200, 28, 150));
        return colors;
    }

    static vector<Color*> GREEN() {
        vector<Color*> colors;
        colors.push_back(new Color("Pacific Avenue", 7000, 35, 200));
        colors.push_back(new Color("North Carolina Avenue", 7000, 35, 200));
        colors.push_back(new Color("Pennsylvania Avenue", 8000, 40, 200));
        return colors;
    }

    static vector<Color*> DARK_BLUE() {
        vector<Color*> colors;
        colors.push_back(new Color("Park Place", 9000, 50, 200));
        colors.push_back(new Color("Boardwalk", 10000, 60, 200));
        return colors;
    }

    map<vector<Color*>, map<string, tuple<int, int, int>>> Map() const {
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

        auto populateMap = [&](const vector<Color*>& colorCategory) {
            auto it = myMap.find(colorCategory);

            if (it == myMap.end()) {
                auto& map = myMap[colorCategory];

                for (const auto& color : colorCategory) {
                    map[color->street_name] = color->color();
                }
            }
        };

        vector<Color*> brown_color = BROWN();
        populateMap(brown_color);
        for (const auto& brown : brown_color) {
            delete brown;
        }

        vector<Color*> light_blue_color = LIGHT_BLUE();
        populateMap(light_blue_color);
        for (const auto& light_blue : light_blue_color) {
            delete light_blue;
        }

        vector<Color*> pink_color = PINK();
        populateMap(pink_color);
        for (const auto& pink : pink_color) {
            delete pink;
        }

        vector<Color*> orange_color = ORANGE();
        populateMap(orange_color);
        for (const auto& orange : orange_color) {
            delete orange;
        }

        vector<Color*> red_color = RED();
        populateMap(red_color);
        for (const auto& red : red_color) {
            delete red;
        }

        vector<Color*> yellow_color = YELLOW();
        populateMap(yellow_color);
        for (const auto& yellow : yellow_color) {
            delete yellow;
        }

        vector<Color*> green_color = GREEN();
        populateMap(green_color);
        for (const auto& green : green_color) {
            delete green;
        }

        vector<Color*> dark_blue_color = DARK_BLUE();
        populateMap(dark_blue_color);
        for (const auto& dark_blue : dark_blue_color) {
            delete dark_blue;
        }

        return myMap;
    }

    tuple<int, int, int> color_information(const map<vector<Color*>, map<string, tuple<int, int, int>>>& myMap, const string& street_name) const {
        for (const auto& outerPair : myMap) {
            auto& map = outerPair.second;
            auto it = map.find(street_name);

            if (it != map.end()) {
                return it->second;
            }
        }

        return make_tuple(-1, -1, -1);
    }
};

// Base Properties class
class Properties {
public:
    Color* color;
    string name;
    int value;
    int rent;
    int cost_built;

    virtual void display() const = 0;
    Properties(int val, int r, int cost) : value(val), rent(r), cost_built(cost) {}
    virtual ~Properties() = default;
};

// House class
class House : public Properties {
public:
    House(int val, int r, int cost) : Properties(val, r, cost) {}
    void display() const override {
        cout << "House: Value $" << value << ", Rent $" << rent << endl;
    }
};

// Hotel class
class Hotel : public Properties {
public:
    Hotel(int val, int r, int cost) : Properties(val, r, cost) {}
    void display() const override {
        cout << "Hotel: Value $" << value << ", Rent $" << rent << endl;
    }
};

// Category class
class Category {
public:
    Color* color;
    Money* money;
    vector<Properties*> property;
    map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;
    int rent_base;
    static const int maximum_property = 4;

    Category() : color(new Color("", 0, 0, 0)), money(new Money(10000)), rent_base(2) {
        myMap = color->Map();
    }

    ~Category() {
        delete color;
        delete money;
        for (auto prop : property) {
            delete prop;
        }
    }

    void upgradeProperties(Properties* ptr, const string& name);
};

// Asset class
class Asset {
public:
    map<string, vector<Properties*>> asset;
    Money* money;
    Color* color;
    map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

    Asset() : color(new Color("", 0, 0, 0)), money(new Money(10000)) {
        myMap = color->Map();
    }

    ~Asset() {
        delete color;
        delete money;
        for (auto& properties : asset) {
            for (auto& prop : properties.second) {
                delete prop;
            }
        }
    }

    void buyAsset(Properties* ptr, const string& name);
    bool search(Properties* ptr);
    void sellAsset(Properties* ptr);
    bool bankruptcy(int rent);
    bool checkRent(int rent);
    void automaticSelling(int rent);
    void manualSelling(int rent);
};

void Category::upgradeProperties(Properties* ptr, const string& name) {
    string response;

    tuple<int, int, int> color_info = color->color_information(myMap, name);
    ptr->value = get<0>(color_info);
    ptr->rent = get<1>(color_info);
    ptr->cost_built = get<2>(color_info);

    cout << "Do you want to upgrade this property (yes or no)? ";
    cin >> response;
    lower_case(response);

    if (response == "yes") {
        if (property.size() < maximum_property) {
            property.push_back(ptr);
            money->chargeIt(ptr->cost_built);
            cout << "Upgraded " << name << " to " << (dynamic_cast<House*>(ptr) ? "House" : "Hotel") << "." << endl;
        } else {
            cout << "Cannot upgrade more properties. Maximum limit reached." << endl;
        }
    }
}

void Asset::buyAsset(Properties* ptr, const string& name) {
    if (search(ptr)) {
        cout << "Property already owned by another player!" << endl;
        return;
    }

    int price = ptr->value;
    if (money->cash >= price) {
        money->chargeIt(price);
        asset[name].push_back(ptr);
        cout << "Bought " << name << "." << endl;
    } else {
        cout << "Not enough cash to buy " << name << "." << endl;
    }
}

bool Asset::search(Properties* ptr) {
    for (const auto& properties : asset) {
        for (const auto& prop : properties.second) {
            if (prop == ptr) {
                return true;
            }
        }
    }
    return false;
}

bool Asset::bankruptcy(int rent) {
    int total_value = money->cash;
    for (const auto& properties : asset) {
        for (const auto& prop : properties.second) {
            total_value += prop->value;
        }
    }
    return total_value < rent;
}

bool Asset::checkRent(int rent) {
    return money->cash >= rent;
}

void Asset::sellAsset(Properties* ptr) {
    int price = ptr->value;
    if (search(ptr)) {
        money->sellIt(price);
        auto& player_assets = asset;
        for (auto& properties : player_assets) {
            auto& vec = properties.second;
            auto it = find(vec.begin(), vec.end(), ptr);
            if (it != vec.end()) {
                vec.erase(it);
                delete ptr;
                cout << "Sold property." << endl;
                return;
            }
        }
    } else {
        cout << "Property not found!" << endl;
    }
}

void Asset::automaticSelling(int rent) {
    if (bankruptcy(rent)) {
        cout << "Player is bankrupt!" << endl;
        return;
    }

    if (checkRent(rent)) {
        auto& player_assets = asset;
        for (auto& properties : player_assets) {
            for (auto& prop : properties.second) {
                sellAsset(prop);
                if (money->cash >= rent) {
                    cout << "Finishing selling..." << endl;
                    return;
                }
            }
        }
        cout << "Could not raise enough funds through automatic selling." << endl;
    } else {
        cout << "Player has enough cash to cover the rent." << endl;
    }
}

void Asset::manualSelling(int rent) {
    if (bankruptcy(rent)) {
        cout << "Player is bankrupt!" << endl;
        return;
    }

    if (checkRent(rent)) {
        cout << "Please enter the property name to sell: ";
        string name;
        cin >> name;
        auto& player_assets = asset;
        auto it = find_if(player_assets[name].begin(), player_assets[name].end(),
                          [&](Properties* prop) { return prop->name == name; });
        if (it != player_assets[name].end()) {
            sellAsset(*it);
        } else {
            cout << "Property not found!" << endl;
        }
    } else {
        cout << "Player has enough cash to cover the rent." << endl;
    }
}

int main() {
    // Example usage
    Category category;
    Asset asset;
    Money money(10000);

    // Create properties
    House* house1 = new House(2000, 2, 50);
    Hotel* hotel1 = new Hotel(5000, 20, 100);

    // Upgrade properties
    category.upgradeProperties(house1, "Mediterranean Avenue");

    // Buy assets
    asset.buyAsset(house1, "Mediterranean Avenue");
    asset.buyAsset(hotel1, "Park Place");

    // Automatic selling
    asset.automaticSelling(3000);

    // Manual selling
    asset.manualSelling(3000);

    return 0;
}
