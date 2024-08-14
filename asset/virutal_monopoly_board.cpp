#include "virtual_monopoly_board.h"
#include <iostream> 
#include <fstream> 
#include <random> 
#include <numeric> 

using namespace std; 
random_device Virtual_Monopoly_Board:: rd; 
mt19937 Virtual_Monopoly_Board:: gen(rd()); 

void Virtual_Monopoly_Board:: positionDeclaration(){
    positionMap[1] = 0;
    positionMap[2] = 0;
    positionMap[3] = 0;
    positionMap[4] = 0; 
}
bool checkPosition(int number){
    return number >= 0 && number < 27;
}
string Virtual_Monopoly_Board::correspondingCityName(int player){
    int position = positionMap[player];
    return city_names[position];
}
void Virtual_Monopoly_Board:: city_name(){ 
    string name;
    vector<Color*> city_vector;  
    tuple<int, int, int> city_information; 
    for (auto itr = myMap.begin(); itr != myMap.end(); itr++){
        city_vector = itr -> first; 
        city.push_back(city_vector);
        auto& map = itr -> second; 
        for (auto city_name = map.begin(); city_name != map.end(); city_name++){
            name = city_name -> first; 
            city_names.push_back(name);
        }
    }
}
// void Virtual_Monopoly_Board::inputFile() {
//     ifstream inputFile; 
//     inputFile.open("cities_names.txt");

//     if ((!inputFile.is_open())){
//         cerr << "No file found in your file." << endl; 
//         exit(1);
//     }
//     int index = 0;
//     while(getline(inputFile, city_names[index])){
//         index++;
//     }    
//     inputFile.close();
// }

int Virtual_Monopoly_Board:: random_number(int begin, int end){
    uniform_int_distribution<>dis(begin, end);
    int number = dis(gen);
    return number; 
}

int Virtual_Monopoly_Board:: throwingDice(){
    return random_number(1, 6);
}
void Virtual_Monopoly_Board:: throwDiceForStep(int player){
    int dice_one = throwingDice();
    int dice_two = throwingDice();
    int steps = dice_one + dice_two;

    position += steps; 
    if (!checkPosition(position)){
        initializePosition(player);
        money -> passGo(player);
    }
    positionMap[player] = position; 
}
void Virtual_Monopoly_Board:: printBoard(int player){
    cout << "Player " << player << "is at " << correspondingCityName(player) << endl; 
}

bool Virtual_Monopoly_Board:: jailCheck(string& cities){
    if (cities != "Jail"){
        return false; 
    }
    return true; 
}

bool Virtual_Monopoly_Board:: diceCheck(int player){
    int user_choice; 
    int dice_one = throwingDice();
    int dice_two = throwingDice();
    do {    
        cout << "You have two options: ";
        cout << "(1) Rolling Double, (2) Rolling More Than 10. ";
        cout << "Please choose 1 of them: ";
        cin >> user_choice; 
    } while (user_choice !=1 || user_choice != 2);
    

    if (user_choice == 1){
        if (dice_one == dice_two){
            money -> chargeIt(player, 50);
            return true; 
        }
        else {
            return false; 
        }
    }

    else if (user_choice == 2){
        if (dice_one + dice_two < 10){
            return false; 
        } else {
            money -> chargeIt(player, 50);
            return true; 
        }
    }
}
void Virtual_Monopoly_Board:: stepMove(int player){
    string cities = correspondingCityName(player);
    if ((!jailCheck(cities))){
        throwDiceForStep(player);
    }
    if ((jailCheck(cities))){
        if (diceCheck(player)){
            throwDiceForStep(player);
        } else {
            cout << "You can try your luck in your next turn. " << endl; 
        }
    }
}



