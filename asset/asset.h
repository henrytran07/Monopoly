#ifndef ASSET_H
#define ASSET_H

#include "color_category.h"
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include "money.h"
#include "properties.h"
#include <tuple> 
using namespace std; 

class Asset { 
    protected: 
        Money* money; 
        Color* color; 
        map<int, map<Color*, vector<Properties*>>> asset;
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

        void lower_case(string &response);
        void userHandleResponse(string &response);

        void eraseAsset(Color* color);
        int netWorth(int player);
        bool ownerVerification(Color* street, int player);
        bool streetLookUp(Color* street); // rename
        int findOwnership(Color* street); // rename 
        bool bankcruptcy(Color* color, int player);
        void cashDeduction(Money* money, int& amount_due, int player, int owner, int sellingAsset);
        void automaticSelling(int rent, int player, int owner);
        void manualSelling(int rent, int player, int owner);

    public:    
        Asset() {
            money = new Money();
            color = new Color();
        }
        Asset(Money* m, Color* c): money(m), color(c) {
            if (color != nullptr) {
                myMap = color -> colorMap();
            } else {
                cerr << "Color object is null" << endl; 
            }
        }

        map<vector<Color*>, map<string, tuple<int, int, int>>> getMyMap() {return myMap;}
        void printAsset() const; 
        void buyAsset(Color* color, int player);
        void sellAsset(Color* color, int player);
        map<int, map<Color*, vector<Properties*>>> getAsset() {return asset;}
        void printAsset() const; 
        void mapUpdate(map<int, map<Color*, vector<Properties*>>>& myMap);
        void modifiedMap(map<int, map<Color*, vector<Properties*>>>& myMap);

        Money* getMoney() {return money;}
        Color* getColor() {return color;}
};

#endif