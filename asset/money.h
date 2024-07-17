
#ifndef MONEY_H
#define MONEY_H

#include <iostream> 

using namespace std; 

class Money {
    public:  
        void chargeIt(int cost);
        void sellIt(int value);
        double payTax();   
        int cash = 2000; 
        const static double tax_rate = 0.3;     
};
#endif 