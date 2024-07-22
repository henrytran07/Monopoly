#ifndef COLOR_CATEGORY_H
#define COLOR_CATEGORY_H

#include <map> 
#include <iostream> 
#include <vector>  
using namespace std; 

class Color {
    protected: 
        string street_name; 
        int price, rent; 
        int cost_built; 

    public: 
        Color(string name, int p, int r, int cost): street_name(name), price(p), rent(r), cost_built(cost) {}
        
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
        map<vector<Color*>, map<string, tuple<int, int, int>>> Map(); 
        tuple<int, int, int> color_information(map<vector<Color*>, map<string, tuple<int, int, int>>> myMap, const string& street_name);
};

#endif 