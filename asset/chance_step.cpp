
#include "chance_card.h"
#include <iostream> 
#include <fstream> 
#include <vector> 
using namespace std; 

void chance_card_description(vector<string>& chance_card){
    ifstream inputFile; 
    inputFile.open("chance_card.txt");

    if ((!inputFile.is_open())){
        cerr << "No file found." << endl; 
        return; 
    }

    int start = 0; 
    while (inputFile >> chance_card[start]){
        start++; 
    }
    inputFile.close();
}

void community_card_description(vector<string>& community_card){
    ifstream inputFile; 
    inputFile.open("community_chest_card.txt");
    if ((!inputFile.is_open())){
        cerr << "No file found. " << endl; 
        return; 
    }

    int start = 0; 
    while(inputFile >> community_card[start]){
        start++; 
    }
    inputFile.close();
}

void ChanceCard::inputFile() {
    chance_card_description(chance_card);
    community_card_description(community_card);
}