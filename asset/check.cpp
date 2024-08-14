#include <iostream>

using namespace std;

void cashDeduction(int &amount_due, int &cash, int owner, int player, int sellingAsset) {
    if (amount_due <= 0) {
        cout << cash << " player cash " << endl;
        return;
    }

    cout << amount_due << " amount due " << endl; 
    
    cash += sellingAsset;
    if (cash >= amount_due) {
        cash -= amount_due;
        amount_due = 0;
    } else {
        amount_due -= cash;
        cash = 0;
    }
    
    cout << cash << " player cash after selling asset" << endl;
    cout << amount_due << " remaining amount due" << endl;
    
    if (amount_due > 0) {
        cashDeduction(amount_due, cash, owner, player, sellingAsset); 
    }
}

int main() {
    int owner = 1; 
    int player = 2; 
    int cash = 500; 
    int rent = 550; 

    int amount_due; 
    if (cash >= rent) {
        amount_due = 0;
        cash -= rent; 
    }

    else if (cash < rent){
        int amount_due = rent - cash;     
        cash = 0; 
        int sellingAsset = 100; 
        cashDeduction(amount_due, cash, owner, player, sellingAsset);
    }
       
    cout << cash << " player cash at the end" << endl;
    cout << amount_due << " remaining amount due at the end" << endl;
}
