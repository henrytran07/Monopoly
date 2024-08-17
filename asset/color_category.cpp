#include <iostream>
#include <map>
#include <vector>
#include <fstream> 
#include <tuple>
#include <string>
#include "color_category.h"

using namespace std;

Color:: Color(string name, int p, int r, int cost): street_name(name), price(p), rent(r), cost_built(cost) {
    inputFile();
}

Color:: Color(): street_name("Go"), price(0), rent(0), cost_built(0) {
    inputFile();
    inititializeMap();
}

vector<Color*> Color::BROWN() {
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

vector<Color*> Color::LIGHT_BLUE() {
    vector<Color*> colors; 

    for (int index = 3; index < 9; index++){
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

vector<Color*> Color::PINK() {
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

vector<Color*> Color:: ORANGE() {
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

vector<Color*> Color:: RED() {
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

vector<Color*> Color:: YELLOW() {
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

vector<Color*> Color:: GREEN() {
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

vector<Color*>Color:: DARK_BLUE() {
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
void Color:: inputFile(){
    ifstream inputFile; 
    inputFile.open("cities_names.txt");
    if (!inputFile.is_open()){
        cerr << "No file found" << endl; 
        exit(1);
    }
    string line; 
    while (getline(inputFile, line)){
        city_name.push_back(line); 
    }
    inputFile.close();
}

void Color:: resetValues(){
    p = 100; 
    r = 50; 
    cost = 50; 
    p_rate = 1.1; 
    r_rate = 1.1; 
    cost_rate = 1.1; 
}

void Color:: marginalAddUp(){
    p_rate += 1.1; 
    r_rate += 1.1; 
    cost_rate += 1.1; 
}

bool Color:: checkNoneValueSpot(const string& city_name){
    if ((city_name == "Go to Jail") || (city_name == "Free Parking") || (city_name == "Chance") || (city_name == "Go")){
        if (city_name == "Go"){
            resetValues();
        }

        temporaryValue(p, r, cost);
        p = 0; 
        r = 0; 
        cost = 0; 
        return true; 
    } else {
        return false; 
    }
}
void Color:: temporaryValue(int p, int r, int cost){
    if ((p == 0) && (r == 0) && (cost == 0)){
        return; 
    }
    
    temp_p = p; 
    temp_r = r; 
    temp_cost = cost; 
}

void Color:: extractTemporaryValue(int &p, int& r, int& cost){
    p = temp_p; 
    r = temp_r; 
    cost = temp_cost; 
}

void Color:: multiplication(){
    p *= p_rate; 
    r *= r_rate; 
    cost *= cost_rate; 
}

void Color:: printMap(const map<vector<Color*>, map<string, tuple<int, int, int>>>& myMap) const {
    if (myMap.empty()){
        cout << "Empty map in colorCategory file " << endl; 
        return; 
    }

    for (const auto & group : myMap){
        cout << "Group of Colors: " << endl; 
        for (const auto& color: group.first)
            cout << " -Street Name: " << color -> getStreetName() << ", Price: $" << color -> getPrice()
                << ", Rent: $" << color -> getRent() << ", Cost to Build: $" << color -> getCostBuilt() << endl; 

        cout << "Color Information Map: " << endl; 
        for (const auto &info : group.second){
            cout << "Street Name: " << info.first << ", Price: $" << get<0> (info.second)
                << ", Rent $" << get<1> (info.second) << ", Cost to Build: $" << get<2> (info.second) << endl; 
        }
    }
}

void Color:: mapUpdate(map<vector<Color*>, map<string, tuple<int, int, int>>> mapColor){
    mapColor = myMap; 
}
map<vector<Color*>, map<string, tuple<int, int, int>>> Color::distributingMap() {
    map<vector<Color*>, map<string, tuple<int, int, int>>> mapCheck;

    auto populateMap = [&](const vector<Color*>& colorCategory) {
        auto& map = mapCheck[colorCategory];

        for (const auto& color : colorCategory) {
            map[color->street_name] = color->color();
        }
        
    };

    vector<Color*> brown_color = Color::BROWN();
    populateMap(brown_color);

    vector<Color*> light_blue_color = Color::LIGHT_BLUE();
    populateMap(light_blue_color);

    vector<Color*> pink_color = Color::PINK();
    populateMap(pink_color);

    vector<Color*> orange_color = Color::ORANGE();
    populateMap(orange_color);

    vector<Color*> red_color = Color::RED();
    populateMap(red_color);

    vector<Color*> yellow_color = Color::YELLOW();
    populateMap(yellow_color);

    vector<Color*> green_color = Color::GREEN();
    populateMap(green_color);

    vector<Color*> dark_blue_color = Color::DARK_BLUE();
    populateMap(dark_blue_color);
    return mapCheck;
}

void Color:: inititializeMap(){
    myMap = distributingMap();
}

map<vector<Color*> , map<string, tuple<int, int, int>>> const Color::colorMap(){
    return myMap; 
}

tuple<int, int, int> Color::color_information(map<vector<Color*>, map<string, tuple<int, int, int>>> myMap, const string& street_name) {
    for (const auto& outerPair : myMap) {
        auto& map = outerPair.second;
        auto it = map.find(street_name);

        if (it != map.end()) {
            return it->second;
        }
    }

    cout << "Street not found in map." << endl; // Debug statement
    return make_tuple(-1, -1, -1);
}

void Color::priceAdjustment(int adjusted_value){
    price = adjusted_value; 
}

void Color::rentAdjustment(int adjusted_rent) {
    rent = adjusted_rent;
}

void Color::costBuiltAdjustment(int adjusted_cost_built){
    cost_built = adjusted_cost_built;
}