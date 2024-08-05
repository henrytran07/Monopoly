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
        int index; 
        int r, p, cost; 
        double p_rate, r_rate, cost_rate; 
    protected:
        string street_name; 
        int price, rent, cost_built; 
        tuple<int, int, int> color() const {
            return make_tuple(price, rent, cost_built);
        }
    public: 
        Color(string name, int p, int r, int cost): street_name(name), price(p), rent(r), cost_built(cost) {
            inputFile();
            initializeValue();
        }
        Color(): street_name(""), rent(0), cost_built(0) {}
        void printMap(const map<vector<Color*>, map<string, tuple<int, int, int>>> &myMap) const; 
        void initializeValue(){
            index = 1; 
        }
        void resetValues() {
            p = 2000; 
            r = 2; 
            cost = 50; 
            p_rate = 1.1; 
            r_rate = 1.1; 
            cost_rate = 1.2; 
        }
        void marginalAddUp(){
            p_rate += 0.1; 
            r_rate += 0.1; 
            cost_rate += 0.1; 
        }
        string getStreetName() const {return street_name;}
        int getPrice() const {return price;}
        int getRent() const {return rent;}
        int getCostBuilt() const {return cost_built;}
        vector<Color*> BROWN() {
            vector<Color*> colors; 
            resetValues();
            while (index < 3){
                Color* city = new Color(city_name[index++], p, r, cost);
                colors.push_back(city);
            }
            return colors; 
        }
        vector<Color*> LIGHT_BLUE() {
            vector<Color*> colors; 
            resetValues();
            while (index < 9){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> PINK() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 12){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> ORANGE() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 15){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> RED() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 18){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> YELLOW() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 21){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> GREEN() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 24){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }

        vector<Color*> DARK_BLUE() {
            vector<Color*> colors; 
            resetValues();
            marginalAddUp();
            while (index < 27){
                colors.push_back(new Color(city_name[index++], p*= p_rate, r *= r_rate, cost *= cost_rate));
            }
            return colors;
        }
     
        map<vector<Color*>, map<string, tuple<int, int, int>>> Map(); 
        tuple<int, int, int> color_information(map<vector<Color*>, map<string, tuple<int, int, int>>> myMap, const string& street_name);
        void intitializeMap();
        map<vector<Color*>, map<string, tuple<int, int, int>>> const colorMap();
        void priceAdjustment(int adjusted_value);
        void rentAdjustment(int adjusted_rent);
        void costBuiltAdjustment(int adjusted_cost_built);
};

#endif 