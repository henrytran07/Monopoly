
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

// Simple Properties class as a placeholder
class Properties {};

// Simple Color class
class Color {
public:
    Color(string name, int price, int rent) : streetName(name), price(price), rent(rent) {}

    string getStreetName() const { return streetName; }
    int getPrice() const { return price; }
    int getRent() const { return rent; }

    tuple<int, int, int> getColorInfo() const {
        // Returning dummy color info for simplicity
        return make_tuple(price, rent, 0);
    }

private:
    string streetName;
    int price;
    int rent;
};

// Simple Money class
class Money {
public:
    Money() {
        // Initialize with some default values for testing
        cash[1] = 1500;
        cash[2] = 1500;
        cash[3] = 1500;
        cash[4] = 1500;
    }

    int getCash(int player) const {
        return cash.at(player);
    }

    void chargeIt(int player, int amount) {
        if (cash[player] >= amount) {
            cash[player] -= amount;
        } else {
            cout << "Not enough cash for player " << player << endl;
        }
    }

    void addCash(int player, int amount) {
        cash[player] += amount;
    }

private:
    map<int, int> cash;
};

// Asset class
class Asset {
public:
    Asset(Money* m) : money(m) {}

    void buyAsset(Color* street, int player) {
        string response;
        tuple<int, int, int> colorIn = street->getColorInfo();
        int value = get<0>(colorIn);

        if (search(street)) {
            if (money->getCash(player) >= value) {
                cout << "Do you want to acquire this asset? (yes/no) ";
                getline(cin, response);
                lower_case(response);
                if (response == "yes") {
                    money->chargeIt(player, value);
                    asset[player][street] = vector<Properties*>();
                    cout << "Player " << player << " acquired " << street->getStreetName() << endl;
                } else {
                    cout << "Player " << player << " chose not to buy" << endl;
                }
            } else {
                cout << "Player " << player << " does not have enough cash to buy " << street->getStreetName() << endl;
            }
        } else if (!search(street) && ownerVerification(street, player)) {
            value *= 2;
            int own = Owner(street);
            if (money->getCash(player) >= value && own != -1) {
                cout << "Do you want to acquire this asset? (yes/no) ";
                getline(cin, response);
                lower_case(response);
                if (response == "yes") {
                    money->chargeIt(player, value);
                    money->addCash(own, value); // Assuming addCash is a method to add cash to the owner
                    auto old_owner = asset.find(own);
                    if (old_owner != asset.end()) {
                        auto& old_properties = old_owner->second;
                        auto old_property = old_properties.find(street);
                        if (old_property != old_properties.end()) {
                            asset[player][street] = old_property->second;
                            old_properties.erase(old_property);
                        }
                    }
                    cout << "Player " << player << " acquired " << street->getStreetName() << endl;
                }
            } else {
                cout << "Not enough cash to acquire this asset or asset owner not found" << endl;
            }
        } else {
            cout << "The asset is already owned or you do not have enough cash" << endl;
        }
    }

    int netWorth(int player) {
        auto properties = asset.find(player);
        int total_properties = 0;
        if (properties != asset.end()) {
            auto& map = properties->second;
            for (auto& itr : map) {
                total_properties += itr.first->getPrice();
            }
        }
        return money->getCash(player) + total_properties;
    }

    bool bankcruptcy(Color* color, int player) {
        int total_asset = netWorth(player);
        if (total_asset < color->getRent()) {
            cout << "Player " << player << " is bankrupt" << endl;
            return true;
        }
        return false;
    }

    void automaticSelling(int rent, int player, int owner) {
        if (rent <= 0) return;

        auto findCheapestProperties = [&](int play) -> Color* {
            auto map = asset.find(play);
            if (map != asset.end()) {
                auto& properties = map->second;
                if (!properties.empty()) {
                    auto cheapest = properties.begin()->first;
                    for (auto& itr : properties) {
                        if (itr.first->getPrice() < cheapest->getPrice()) {
                            cheapest = itr.first;
                        }
                    }
                    return cheapest;
                }
            }
            return nullptr;
        };

        Color* cheapest = findCheapestProperties(player);
        if (cheapest) {
            int value = cheapest->getPrice();
            money->addCash(player, value);
            money->chargeIt(player, rent);
            money->addCash(owner, rent);
            rent -= value;
            eraseAsset(cheapest);
            automaticSelling(rent, player, owner);
        }
    }

    void manualSelling(int rent, int player, int owner) {
        if (rent <= 0) return;

        string response;
        auto map = asset.find(player);
        if (map != asset.end()) {
            auto& it = map->second;
            for (auto& itr : it) {
                Color* color = itr.first;
                cout << "Asset: " << color->getStreetName() << " - Value: $" << color->getPrice() << endl;
                cout << "Do you want to sell this asset? (yes/no) ";
                getline(cin, response);
                lower_case(response);
                if (response == "yes") {
                    int value = color->getPrice();
                    money->addCash(player, value);
                    money->chargeIt(player, rent);
                    money->addCash(owner, rent);
                    rent -= value;
                    eraseAsset(color);
                }
                if (rent <= 0) return;
            }
        }
        manualSelling(rent, player, owner);
    }

    void sellAsset(Color* color, int player) {
        string response;
        int rent = color->getRent();
        int cash = money->getCash(player);
        int owner = Owner(color);

        if (rent > cash) {
            if (!bankcruptcy(color, player)) {
                cout << "Your cash is less than the rent. Do you want to manually sell your assets or ";
                cout << "automatically sell them? (a/b): ";
                getline(cin, response);
                lower_case(response);
                if (response == "a") {
                    manualSelling(rent - cash, player, owner);
                } else if (response == "b") {
                    automaticSelling(rent - cash, player, owner);
                }
            }
        } else {
            cout << "Charging $" << rent << " for rent" << endl;
            money->chargeIt(player, rent);
            money->addCash(owner, rent);
        }
    }

private:
    void lower_case(string &response) {
        transform(response.begin(), response.end(), response.begin(), ::tolower);
    }

    bool ownerVerification(Color* street, int player) {
        for (int play = 1; play <= 4; play++) {
            auto map = asset.find(play);
            if (map != asset.end()) {
                auto it = map->second.find(street);
                if (it != map->second.end() && play == player) {
                    return true;
                }
            }
        }
        return false;
    }

    bool search(Color* street) {
        for (int play = 1; play <= 4; play++) {
            auto map = asset.find(play);
            if (map != asset.end()) {
                if (map->second.find(street) != map->second.end()) {
                    return false;
                }
            }
        }
        return true;
    }

    int Owner(Color* street) {
        for (int play = 1; play <= 4; play++) {
            auto map = asset.find(play);
            if (map != asset.end()) {
                if (map->second.find(street) != map->second.end()) {
                    return play;
                }
            }
        }
        return -1;
    }

    void eraseAsset(Color* color) {
        int owner = Owner(color);
        auto map = asset.find(owner);
        if (map != asset.end()) {
            auto& it = map->second;
            it.erase(color);
        }
    }

    Money* money;
    map<int, map<Color*, vector<Properties*>>> asset; // Map player IDs to their assets
};

// Main function for testing
int main() {
    Money money;
    Asset assetManager(&money);

    Color parkPlace("Park Place", 350, 35);
    Color boardwalk("Boardwalk", 400, 50);

    assetManager.buyAsset(&parkPlace, 1); // Player 1 buys Park Place
    assetManager.buyAsset(&boardwalk, 2); // Player 2 buys Boardwalk

    // Simulate rent scenario
    assetManager.sellAsset(&parkPlace, 1); // Player 1 pays rent for Park Place

    return 0;
}
