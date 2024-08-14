#ifndef VIRTUAL_BOARD_H
#define VIRTUAL_BOARD_H

#include <iostream> 
#include <vector> 
#include <random> 
#include <numeric> 
#include <tuple> 
#include "money.h"
#include "color_category.h"
#include "asset.h"

using namespace std; 

class Virtual_Board {
    private: 
        Asset* asset = new Asset(asset -> getMoney(), asset -> getColor());
        Upgrade* upgrade = new Upgrade(asset);
    public: 
        Virtual_Board(Upgrade* upg): upgrade(upg) {
            // upgrade = new Upgrade(asset)
        }
};
#endif