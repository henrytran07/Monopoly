#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <vector>
#include <map>
#include "money.h"
using namespace std;


class Properties {
public:
    string name;
    int value;
    int rent;
    int cost_built;

    virtual void display() const = 0; 
    Properties(int val, int r, int cost) :  value(val), rent(r), cost_built(cost) {}
    virtual ~Properties() = default; 
};

class House : public Properties {
public:
    House(int val, int r, int cost) : Properties(val, r, cost) {}
    void display() const override {
        cout << "House: Value $" << value << ", Rent $" << rent << endl;
        
    }
};

class Hotel : public Properties {
public:
    Hotel(int val, int r, int cost) : Properties(val, r, cost) {}
    void display() const override {
        cout << "Hotel: Value $" << value << ", Rent $" << rent << endl; 
    }
};

class Category {
public:
    int cash;
    vector<Properties*> property;
    Money* money;
    int rent_base;
    static const int maximum_property = 4; 
    void upgradeProperties(Properties* ptr);
};

class Asset {
public:
    int cash;
    map<int, map<string, vector<Properties*>>> asset;
    Money* money;

    void buyAsset(Properties* ptr, int player, const string& name);
    bool search(Properties* ptr);
    int owner(Properties* ptr);
    bool bankruptcy(int player, int rent);
    bool checkRent(int rent);
    void sellAsset(Properties* ptr, int player);
    void automaticSelling(int rent, int player);
};

void lower_case(string &response);

#endif 
