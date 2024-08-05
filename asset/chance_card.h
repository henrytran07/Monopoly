
#ifndef CHANCE_CARD_H
#define CHANCE_CARD_H

#include <iostream> 
#include <vector> 
#include <map> 
using namespace std;
void chance_card_description(vector<string>& chance_card);
void community_card_description(vector<string>& community_card);


class Postion{
    private: 
        int row; 
        int col; 
    public: 
        void addStep();
        void deduceStep();
};
struct Action {
    vector<Postion*> position; 
};

class ChanceCard{
    private: 
        vector<string> chance_card;
        vector<string> community_card;
        void inputFile();
        map<string, vector<Action*>> myMap; 
};
#endif