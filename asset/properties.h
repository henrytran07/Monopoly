
#ifndef PROPERTIES_H
#define PROPERTIES_H
#include "color_category.h"
#include <iostream> 
#include "asset.h"
#include <vector> 
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

class Upgrade: public Asset {
    private: 
        Asset* asset; 
        map<int, map<Color*, vector<Properties*>>> myMap; 

        int maximum_houses = 4;
        vector<Properties*>properties;
        Asset* asset; 
        // Update this rent base later 
        const double rent_rate = 1.1;
        const double value_rate = 1.1;
        const double cost_built_rate = 1.1;

        void addProperties(map<int, map<Color*, vector<Properties*>>> &map_color, Color* color, int player, Asset* asset, Upgrade* upgrade, Money* money);
        void houseUpgrade(Color* color, int player);
        void hotelUpgrade(Color* color, int player);
        void valueAdjustment(Color* color, int player);
    public: 
        Upgrade(Asset* asst): Asset(asst -> getMoney(), asst -> getColor()), asset(asst){
            if (asst != nullptr){
                myMap = asst -> getAsset();
            } else {
                cout << "null pointer" << endl; 
            }
        }
        void updateVector(const vector<Properties*> &prop);
        void upgradeProperties(Color* color, int player);
};
#endif 