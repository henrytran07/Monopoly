
#include "assets.h" 
#include <iostream> 
#include <vector> 

using namespace std; 

struct Properties {
    int value, rent; 
    Properties(int x, int y): value(x), rent(y) {}
    virtual ~Properties() = default; 
};
struct House : public Properties{
    House(int x, int y): Properties(x, y) {}
};

struct Hotel : public Properties {
    Hotel(int x, int y): Properties(x, y) {}
};

class Money {
    private: 
        const double tax_rate = 0.3; 
        int cash;
        vector<Properties*> properties; 

        void addProperty(vector<Properties*>& property, Properties* ptr);
        void getCharged(int rent);
        void sellProperty(vector<Properties*>& property);
        bool banckruptcy(int rent);
    public: 
        Money(int x): cash(x) {}
        ~Money();

        void addProperty(Properties* property);
        void charge(int rent); 
        double PayTax();
};

Money:: ~Money() {
    for (auto property: properties){
        delete(property);
    }
}
void Money:: getCharged(int rent){
    if (banckruptcy(rent)){
        cout << "You are bankcrupted." << endl; 
        return; 
    }
    if (cash < rent){
        cout << "Not enough to proceed the transaction. Selling property..." << endl; 
        while ((cash < rent)){
            sellProperty(properties); 
        }    
    }
    cash -= rent; 
}

void Money:: sellProperty(vector<Properties*>& property){
    if (property.empty())
        return; 
    Properties* ptr = property.back();
    property.pop_back();
    cout << "Selling properties worth " << ptr -> value << endl; 
    cash += ptr -> value; 
    delete ptr; 

    sellProperty(property);
}

void Money:: charge(int rent){
    getCharged(rent);
}

void lower_case(string response){
    for (char word: response){
        word = tolower(word);
    }
}
void Money:: addProperty(vector<Properties*>& property, Properties* ptr){
    string response; 
    if (cash >= ptr -> value){
        cout << "Do you want to acquire this property (yes/no)? ";
        cin >> response; 
        lower_case(response);
        if (response == "yes"){
            property.push_back(ptr);
            cash -= ptr -> value; 
        }
    }
}

void Money:: addProperty(Properties* property){
    addProperty(properties, property);
}

double Money:: PayTax(){
    int net_worth = 0;  
    for (const auto& property: properties){
        net_worth += property -> value; 
    } 
    double tax = tax_rate * net_worth; 
    return tax; 
}

bool Money:: banckruptcy(int rent) {
    int total_net_worth = 0; 
    for (const auto& property: properties){
        total_net_worth += property -> value; 
    }

    if (total_net_worth + cash < rent){
        return true; 
    }
    return false;
}