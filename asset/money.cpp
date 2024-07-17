
#include "money.h"
#include <iostream> 

using namespace std; 

void Money:: chargeIt(int cost){
    cash -= cost; 
}

void Money:: sellIt(int value){
    cash += value; 
}
   