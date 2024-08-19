#include "CommunityChestCard.h"
#include <iostream> 

using namespace std; 

void CommunityChestCard:: cardInputFile(){
    ifstream inputFile; 
    inputFile.open("community_chest_card/community_chest_card.txt");

    if ((!inputFile.is_open())){
        cerr << "No file found: community_chest_card.txt" << endl; 
        return; 
    }

    string line; 
    while(getline(inputFile, line)){
        community_chest_card.push_back(line);
    }

    if (community_chest_card.empty()){
        cout << "community_chest_card vector is empty" << endl; 
    }

    inputFile.close();
}

vector<string> CommunityChestCard:: getCommunityChestCard(){
    return community_chest_card; 
}