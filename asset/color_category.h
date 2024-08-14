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
        Color(string name, int p, int r, int cost): street_name(name), price(p), rent(r), cost_built(cost) {
            inputFile();
        }
        Color(): street_name(""), price(0), rent(0), cost_built(0) {
            inputFile();
            inititializeMap();
        }
        void printMap(const map<vector<Color*>, map<string, tuple<int, int, int>>> &myMap) const; 
        bool checkNoneValueSpot(const string& city_name);

        string getStreetName() const {return street_name;}
        int getPrice() const {return price;}
        int getRent() const {return rent;}
        int getCostBuilt() const {return cost_built;}
        vector<Color*> BROWN() {
            vector<Color*> colors; 
            resetValues();

            for (int index = 0; index < 3; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement.
                } else {
                    // No conditional requiremnt in this clause. 
                }

                Color* city = new Color(city_name[index], p, r, cost);
                colors.push_back(city);
                extractTemporaryValue(p, r, cost);
            }
            
            if (colors.empty()) {
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> BROWN() function" << endl; 
            }

            return colors; 
        }
        vector<Color*> LIGHT_BLUE() {
            vector<Color*> colors; 

            for (int index = 3; index , 9; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement. 
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> LIGHT_BLUE() function" << endl; 
            }
            return colors;
        }

        vector<Color*> PINK() {
            vector<Color*> colors; 

            for (int index = 9; index < 12; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement. 
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> PINK() FUNCTION" << endl; 
            }
            return colors; 
        }

        vector<Color*> ORANGE() {
            vector<Color*> colors; 

            for (int index = 12; index < 15; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requireemnt in this if-statement.
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r , cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> ORANGE() FUNCTION" << endl; 
            }
            return colors; 
        }

        vector<Color*> RED() {
            vector<Color*> colors; 

            for (int index = 15; index < 18; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> RED() FUNCTION" << endl; 
            }
            return colors; 
        }

        vector<Color*> YELLOW() {
            vector<Color*> colors; 
   
            for (int index = 18; index < 21; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement. 
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> YELLOW() FUNCTION" << endl; 
            }
            
            return colors;
        }

        vector<Color*> GREEN() {
            vector<Color*> colors; 
            
            for (int index = 21; index < 24; index++){
                if((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement.
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> GREEN() FUNCTION" << endl; 
            }
            
            return colors; 
        }

        vector<Color*> DARK_BLUE() {
            vector<Color*> colors; 

            for (int index = 24; index < 27; index++){
                if ((checkNoneValueSpot(city_name[index]))){
                    // no need to add additional requirement in this if-statement
                } else {
                    marginalAddUp();
                    multiplication();
                }

                colors.push_back(new Color(city_name[index], p, r, cost));
                extractTemporaryValue(p, r, cost);
            }

            if (colors.empty()){
                cout << "EMPTY VECTOR IN VECTOR<COLOR*> DARK_BLUE() FUNCTION" << endl; 
            }

            return colors; 
        }
     
        map<vector<Color*>, map<string, tuple<int, int, int>>> distributingMap(); 
        tuple<int, int, int> color_information(map<vector<Color*>, map<string, tuple<int, int, int>>> myMap, const string& street_name);
        void inititializeMap();
        map<vector<Color*>, map<string, tuple<int, int, int>>> const colorMap();
        void priceAdjustment(int adjusted_value);
        void rentAdjustment(int adjusted_rent);
        void costBuiltAdjustment(int adjusted_cost_built);
};

#endif 