#ifndef COLOR_CATEGORY_H
#define COLOR_CATEGORY_H

#include <map> 
#include <iostream> 
#include <vector>  
#include <tuple> 
using namespace std; 

class Color {
    private: 
        vector<string> city_name; 
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap; 
        void inputFile();
        int r, p, cost; 
        double p_rate, r_rate, cost_rate; 
        int temp_p, temp_r, temp_cost; 

        void resetValues();
        void marginalAddUp();

        void temporaryValue(int p, int r, int cost);
        void extractTemporaryValue(int &p, int& r, int& cost);
        void multiplication();
    protected:
        string street_name; 
        int price, rent, cost_built; 
        tuple<int, int, int> color() const {
            return make_tuple(price, rent, cost_built);
        }
    public: 
        Color(string name, int p, int r, int cost);

        Color();
        void printMap(const map<vector<Color*>, map<string, tuple<int, int, int>>> &myMap) const; 
        bool checkNoneValueSpot(const string& city_name);

        string getStreetName() const {return street_name;}
        int getPrice() const {return price;}
        int getRent() const {return rent;}
        int getCostBuilt() const {return cost_built;}

        vector<string> city_names() {return city_name;}
        vector<Color*> BROWN();
        vector<Color*> LIGHT_BLUE();

        vector<Color*> PINK();

        vector<Color*> ORANGE();

        vector<Color*> RED();

        vector<Color*> YELLOW();

        vector<Color*> GREEN();

        vector<Color*> DARK_BLUE();
     
        map<vector<Color*>, map<string, tuple<int, int, int>>> distributingMap(); 
        tuple<int, int, int> color_information(map<vector<Color*>, map<string, tuple<int, int, int>>> myMap, const string& street_name);
        void inititializeMap();
        map<vector<Color*>, map<string, tuple<int, int, int>>> const colorMap();
        void priceAdjustment(int adjusted_value);
        void rentAdjustment(int adjusted_rent);
        void costBuiltAdjustment(int adjusted_cost_built);

        void mapUpdate(map<vector<Color*>, map<string, tuple<int, int, int>>> mapColor);
};

#endif 