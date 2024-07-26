#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <string>
#include "color_category.h"

using namespace std;

map<vector<Color*>, map<string, tuple<int, int, int>>> Color::Map() {
    map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;

    auto populateMap = [&](const vector<Color*>& colorCategory) {
        auto& map = myMap[colorCategory];

        for (const auto& color : colorCategory) {
            map[color->street_name] = color->color();
            cout << "Adding: " << color->street_name << endl;
        }
    };

    vector<Color*> brown_color = Color::BROWN();
    populateMap(brown_color);
    for (const auto brown : brown_color) {
        delete brown;
    }

    vector<Color*> light_blue_color = Color::LIGHT_BLUE();
    populateMap(light_blue_color);
    for (const auto light_blue : light_blue_color) {
        delete light_blue;
    }

    vector<Color*> pink_color = Color::PINK();
    populateMap(pink_color);
    for (const auto pink : pink_color) {
        delete pink;
    }

    vector<Color*> orange_color = Color::ORANGE();
    populateMap(orange_color);
    for (const auto orange : orange_color) {
        delete orange;
    }

    vector<Color*> red_color = Color::RED();
    populateMap(red_color);
    for (const auto red : red_color) {
        delete red;
    }

    vector<Color*> yellow_color = Color::YELLOW();
    populateMap(yellow_color);
    for (const auto yellow : yellow_color) {
        delete yellow;
    }

    vector<Color*> green_color = Color::GREEN();
    populateMap(green_color);
    for (const auto green : green_color) {
        delete green;
    }

    vector<Color*> dark_blue_color = Color::DARK_BLUE();
    populateMap(dark_blue_color);
    for (const auto dark_blue : dark_blue_color) {
        delete dark_blue;
    }

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
