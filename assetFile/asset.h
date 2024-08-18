#ifndef ASSET_H
#define ASSET_H
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <tuple> 
#include "/Users/tranhuuloc/Documents/DSA_CODE/Monopoly/money/money.h"
#include "/Users/tranhuuloc/Documents/DSA_CODE/Monopoly/color_category/color_category.h"
#include "/Users/tranhuuloc/Documents/DSA_CODE/Monopoly/virtual_monopoly_board/virtual_monopoly_board.h"

using namespace std; 

class Money;
class Virtual_Monopoly_Board;
class Upgrade; 
class Properties: public Color {
    public: 
        virtual void display() const = 0; 
        Properties(string nm, int val, int r, int cost);
        virtual ~Properties() = default; 
};

class House: public Properties {
    public: 
        House(string nm, int val, int r, int cost);
        void display() const override;
};

class Hotel: public Properties {
    public: 
        Hotel(string nm, int val, int r, int cost);
        void display() const override; 
};

class Asset { 
    protected: 
        Money* money; 
        Color* color; 
        Upgrade* upgrade; 
        Virtual_Monopoly_Board* vmb; 
        map<int, map<Color*, vector<Properties*>>> asset;
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

        map<int, string> playerName; 
        vector<string> special_space = {"Go", "Go to Jail", "Chance", "Free Parking", "Community Chest"};
        
        void userTrialInput(string &response, const string& first_condition, const string& second_condition);

        bool ownerVerification(Color* street, int player);
        bool streetLookUp(Color* street); 

        
        int findOwner(Color* street);
        
        void cashDeduction(Money* money, int& amount_due, int player, int owner, int sellingAsset);
        void eraseAsset(Color* color);

    public:    
        Asset();
        Asset(Money* m, Color* c);
        virtual~Asset() = default; 

        void userHandleResponse(string& response, const string& first_condition, const string& second_condition);
        void updatedNameMap(map<int, string> &mapName);

        map<vector<Color*>, map<string, tuple<int, int, int>>> getMyMap();
        void printAsset(); 

        int calculatingPlayerNetWorth(int player);
        void buyAsset(Color* color, int player);

        bool bankruptcy(Color* color, int player);
        void automaticSelling(int rent, int player, int owner);
        void manualSelling(int rent, int player, int owner, const string& first_condition, const string& second_condition);
        void sellAsset(Color* color, int player);
        map<int, map<Color*, vector<Properties*>>> getAsset() {return asset;}

        void mapUpdate(map<int, map<Color*, vector<Properties*>>>& myMap);
        void modifiedMap(map<int, map<Color*, vector<Properties*>>>& myMap);

        void playerAssetElimination(int player);
        Money* getMoney(); 
        Color* getColor();
};

class Upgrade: public Asset {
    private: 
        Asset* asst; 
        vector<Properties*>properties;
        map<int, map<Color*, vector<Properties*>>> myMap; 

        int maximum_houses = 4;
        const double rent_rate = 1.1;
        const double value_rate = 1.1;
        const double cost_built_rate = 1.1;

        void addProperties(map<int, map<Color*, vector<Properties*>>> &map_color, Color* color, int player, Asset* asset, Upgrade* upgrade, Money* money);
        void houseUpgrade(Color* color, int player, const string& first_condition, const string& second_condition);
        void hotelUpgrade(Color* color, int playe, const string& first_condition, const string& second_condition);
        void valueAdjustment(Color* color, int player);
    public: 
        Upgrade(Asset* asst);
        void upgradeProperties(Color* color, int player);
        void mapChange (map<int, map<Color*, vector<Properties*>>>&asset);
};

#endif