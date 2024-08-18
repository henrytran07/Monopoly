#ifndef COMMUNITY_CHEST_CARD_H
#define COMMUNITY_CHEST_CARD_H

#include <vector> 
#include <iostream> 
#include <fstream> 
using namespace std; 
class CommunityChestCard{
    private: 
        vector<string> community_chest_card; 
        void cardInputFile();
    public:     
        CommunityChestCard(){
            cardInputFile();
        }

        vector<string> getCommunityChestCard();
};
#endif