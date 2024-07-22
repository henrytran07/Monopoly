#ifndef TRY_H
#define TRY_H

#include "color_category.h"
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include "money.h"
#include <tuple> 
using namespace std; 

class Properties: public Color {
    public: 
        virtual void display() const = 0; 
        Properties(string nm, int val, int r, int cost) : Color(nm, val, r, cost) {}
        virtual ~Properties() = default; 
};

class House: public Properties {
    public: 
        House(string nm, int val, int r, int cost): Properties(nm, val, r, cost) {}
        void display() const override {
            cout << "House on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl; 
        }
};

class Hotel: public Properties {
    public: 
        Hotel(string nm, int val, int r, int cost): Properties(nm, val, r, cost) {}
        void display() const override {
            cout << "Hotel on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl; 
        }
};

class Asset { 
    protected: 
        Money* money; 
        Color* color; 
        map<int, map<Color*, vector<Properties*>>> asset;
        tuple<int, int, int> colorInfo(Color* street) const; 

        void eraseAsset(Color* color);
        int netWorth(int player);
        bool ownerVerification(Color* street, int player);
        bool search(Color* street);
        int Owner(Color* street);
        bool bankcruptcy(Color* color, int player);
        void automaticSelling(int rent, int player, int owner);
        void manualSelling(int rent, int player, int owner);
    public:    
        Asset(Money* m): money(m) {} 
        void buyAsset(Color* color, int player);
        void sellAsset(Color* color, int player);
};
class Upgrade: public Asset {
    private: 
        Money* money; 
        vector<Properties*>properties[4];
        map<int, map<string, vector<Properties*>>> search; 
        static const int rent_base = 2;
    public: 
        void upgradeProperties(Properties* ptr, const string& name);
};

#endif