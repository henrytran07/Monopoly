#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> 
#include <fstream>
#include <iomanip>
#include <random> 
#include <tuple> 
#include <numeric> 
using namespace std;

class Money {
private:
    map<int, int> cash;
    int player;
    // Asset* asset; 
    static double tax_rate; 

    void cashDeclaration() {
        // for (int i = 1; i <= 4; i++) {  // Assuming 4 players
        //     cash[i] = 5760;
        // }

        cash[1] = 600; 
        cash[2] = 100; 
        cash[3] = 100; 
    }

public:
    Money() {
        cashDeclaration();
    }
    static void initializeValue(){
        tax_rate = 0.3; 
    }
    int getCash(int player) {
        return cash.at(player);
    }

    void chargeIt(int player, int cost) {
        cash[player] -= cost;
    }

    void sellIt(int player, int value) {
        cash[player] += value;
    }

    void passGo(int player) {
        cout << endl; 
        cout << "Player " << player << " passes Go" << endl; 
        cout << endl; 
        sellIt(player, 200);  // Assuming passing Go gives $200
    }

    void eraseMap(int player){
        cash.erase(player);
    }
    // double payTax(int player){
    //     map<int, map<Color*, vector<Properties*>>> asst = asset -> getAsset(); 
    //     int total_asset = 0; 
    //     auto map = asst.find(player);
    //     if (map != asst.end()){
    //         for (const auto& prop : map -> second){
    //             total_asset += prop.first -> getPrice();
    //         }
    //     }
    //     double tax = tax_rate * total_asset; 
    //     cash[player] -= static_cast<int> (tax);
    //     return tax; 
    // }
};

class Color {
public: 
    vector<string> city_name;
    map<vector<Color*>, map<string, tuple<int, int, int>>> myMap; 
    void inputFile() {
        ifstream inputFile("cities_names.txt");

        if (!inputFile.is_open()) {
            cerr << "No file is found." << endl;
            exit(1);
        }

        string line;
        while (getline(inputFile, line)) {
            city_name.push_back(line);
        }

        inputFile.close();
    }
    
    int index, r, p, cost; 
    int temp_p, temp_r, temp_cost; 
    double p_rate, r_rate, cost_rate;   
protected: 
    string street_name; 
    int price, rent, cost_built; 
    tuple<int, int, int> color() const {
        return make_tuple(price, rent, cost_built);
    }
public: 
    Color(string name, int p, int r, int cost): street_name(name), price(p), rent(r), cost_built(cost) {
        inputFile();
        initializeValue();
        // initializeMap();
    }   
    Color(): street_name("Go"), price(0), rent(0), cost_built(0){
        inputFile();
        initializeValue();
        initializeMap();
    }
    void printMap(const map<vector<Color*>, map<string, tuple<int, int, int>>>& myMap) const {
        for (const auto &group : myMap) {
            cout << "Group of Colors:" << endl;
            for (const auto &color : group.first) {
                cout << "  - Street Name: " << color->getStreetName() << ", Price: $" << color->getPrice() 
                    << ", Rent: $" << color->getRent() << ", Cost to Build: $" << color->getCostBuilt() << endl;
            }   

            cout << "Color Information Map:" << endl;
            for (const auto &info : group.second) {
                cout << "  Street Name: " << info.first << ", Price: $" << get<0>(info.second)
                    << ", Rent: $" << get<1>(info.second) << ", Cost to Build: $" << get<2>(info.second) << endl;
            }
        }
    }

    void resetValues(){
        p = 100; 
        r = 50; 
        cost = 50; 
        p_rate = 1.1; 
        r_rate = 1.1;
        cost_rate = 1.2;
    }

    void marginalAddUp(){
        p_rate += 0.1; 
        r_rate += 0.1; 
        cost_rate += 0.1; 
    }   

    void temporaryValue(int p, int r, int cost){
        if (p == 0 && r == 0 && cost == 0){
            return; 
        }
        temp_p = p; 
        temp_r = r; 
        temp_cost = cost; 
        cout << endl; 
    }

    void extractTemporaryValue(int &p, int &r, int &cost){
        p = temp_p;  
        r = temp_r;  
        cost = temp_cost; 
    }
    vector<string> city_names() {return city_name;}   
    string getStreetName() const {return street_name;}
    int getPrice() const {return price;}
    int getRent() const {return rent;}
    int getCostBuilt() const {return cost_built;}
    
    bool checkNoneValueSpot(const string& city_name){
        cout << city_name << ": city_name" << endl; 
        if ((city_name == "Go to Jail") || (city_name == "Free Parking") || (city_name == "Community Chest") || (city_name == "Chance") || (city_name == "Go")){
            if (city_name == "Go"){
                resetValues();
            }
            temporaryValue(p, r, cost);
            p = 0; 
            r = 0; 
            cost = 0; 
            return true; 
        }
        else {
            // resetValues();
            // extractTemporaryValue(p, r, cost);
            return false; 
        } 
    }   

    void multiplication(){
        p *= p_rate; 
        r *= r_rate; 
        cost *= cost_rate; 
    }
    void printVector() const {
        for (size_t i = 0; i < city_name.size(); i++) {
            cout << city_name[i] << ": city_name element." << endl;
        }
    }

    vector<Color*> BROWN() {
        vector<Color*> colors; 
        for (int index = 0; index < 3; ++index){
            if (checkNoneValueSpot(city_name[index])){
                // No need to add additional requirement in this one.
                
            } else {
                // No conditional requirement for this one. 
            }
            Color* city = new Color(city_name[index], p, r, cost);
            colors.push_back(city);
            extractTemporaryValue(p, r, cost);
        }
        return colors; 
    }

    vector<Color*> LIGHT_BLUE() {
        vector<Color*> colors; 
        // resetValues();
        for (int index = 3; index < 9; ++index){
            if (checkNoneValueSpot(city_name[index])){
                // no need to add additional requirement in this one. 
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            Color* city = new Color(city_name[index], p, r, cost);
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> PINK() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int index = 9; index < 12; ++index){
            if (checkNoneValueSpot(city_name[index])){
                // no need to add additional requirement in this one. 
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> ORANGE() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int index = 12; index < 15; ++index){
            if (checkNoneValueSpot(city_name[index])){
                //no need to add additional requirement in this one. 
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> RED() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int index = 15; index < 18; ++index){
            if (checkNoneValueSpot(city_name[index])){
                // no need to add additional requirement in this one
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> YELLOW() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int indec = 18; index < 21; ++index){
            if (checkNoneValueSpot(city_name[index])){
                //no need to add additional requirement in this one. 
            } else{
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> GREEN() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int index = 21; index < 24; ++index){
            if ((checkNoneValueSpot(city_name[index]))){
                // no need to add additional requirement in this one
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    vector<Color*> DARK_BLUE() {
        vector<Color*> colors; 
        // resetValues();
        // marginalAddUp();
        for (int index = 24; index < 27; ++index){
            if ((checkNoneValueSpot(city_name[index]))){
                // no need to add additional requirement in this one. 
            } else {
                marginalAddUp();
                multiplication();
            }
            colors.push_back(new Color(city_name[index], p, r, cost));
            extractTemporaryValue(p, r, cost);
        }
        return colors;
    }

    map<vector<Color*>, map<string, tuple<int, int, int>>> Map(){
        map<vector<Color*>, map<string, tuple<int, int, int>>> mapCheck; 
        auto populateMap = [&] (const vector<Color*>& colorCategory){
            auto& map = mapCheck[colorCategory];

            for (const auto& color: colorCategory){
                map[color->street_name] = color->color();
            }
        };
        vector<Color*> brown_color = BROWN();
        populateMap(brown_color);

        vector<Color*> pink_color = PINK();
        populateMap(pink_color);
        
        vector<Color*> orange_color = ORANGE();
        populateMap(orange_color);
        

        vector<Color*> red_color = RED();
        populateMap(red_color);
        // for (auto color : red_color) delete color;

        vector<Color*> yellow_color = YELLOW();
        populateMap(yellow_color);
        // for (auto color : yellow_color) delete color;

        vector<Color*> green_color = GREEN();
        populateMap(green_color);
        // for (auto color : green_color) delete color;

        vector<Color*> dark_blue_color = DARK_BLUE();
        populateMap(dark_blue_color);
        // for (auto color : dark_blue_color) delete color;

        return mapCheck; 
    }
     void initializeValue() {
        index = 0;  // Start at 0 to avoid skipping the first city name
    }
    void initializeMap(){
        myMap = Map();  
    }

    map<vector<Color*>, map<string, tuple<int, int, int>>> const colorMap() {
        return myMap;
    }

    tuple<int, int, int> color_information(const map<vector<Color*>, map<string, tuple<int, int, int>>>& myMap, const string& street_name) const {
        for (const auto& outerPair : myMap) {
            auto& map = outerPair.second; 
            auto it = map.find(street_name);

            if (it != map.end()) {
                cout << "Street is found" << endl; 
                return it->second; 
            }
        }

        cout << "Street not found in map." << endl; 
        return make_tuple(-1, -1, -1);
    }

    void priceAdjustment(int adjusted_value){
        price = adjusted_value; 
    }

    void rentAdjustment(int adjusted_rent){
        rent = adjusted_rent; 
    }

    void costBuiltAdjustment(int adjusted_cost_built){
        cost_built = adjusted_cost_built; 
    }
};


class Properties: public Color {
    public: 
        virtual void display() const = 0; 
        Properties(string nm, int val, int r, int cost): Color(nm, val, r, cost) {}
        virtual ~Properties() = default; 
};

class House: public Properties {
    public: 
        House(string nm, int val, int r, int cost): Properties(nm, val, r, cost) {}
        void display() const override {
            cout << "House on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl;
        }
};

class Hotel: public Properties {
    public: 
        Hotel(string nm, int val, int r, int cost) : Properties(nm, val, r, cost) {}
        void display() const override {
            cout << "Hotel on the streetname " << street_name << ": Value $" << price << ", Rent $" << rent << endl; 
        }
};

class Upgrade; 
class Virtual_Monopoly_Board; 
class Asset {
    protected: 
        Money* money; 
        Color* color;
        Virtual_Monopoly_Board* vmb; 
        map<int, map<Color*, vector<Properties*>>> asset; 
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap ;
        Upgrade* upgrade; 

        map<int, string> playerName;

        void userHandleResponse(string &response){
            while (response != "yes" && response != "no"){
                cout << "Your response is neither yes nor no. Could you choose your option again? ";
                cin >> response; 
                lower_case(response);
            }
        }

        void lower_case(string& response){
            transform(response.begin(), response.end(), response.begin(), ::tolower);
            userHandleResponse(response);
        }
        
        bool ownerVerification(Color* street, int player) {
        if (street == nullptr) return false;

        // Search for the player
            auto mapIt = asset.find(player);
        // Search for the street
            auto& innerMap = mapIt->second;
            auto streetIt = innerMap.find(street);
            if (streetIt != innerMap.end()) {
                return true;
            }

            return false;
        }



        bool streetLookUp(Color* street){
            if (street == nullptr) return false;
            auto checkStreetPresence = [&] (int player){
                auto map = asset.find(player);
                if (map != asset.end()){
                    auto properties = map -> second; 
                    auto it = properties.find(street);
                    if (it != properties.end()){
                        return true; 
                    }
                }
                return false; 
            };

            for (int play = 1; play <= 4; play++){
                if (checkStreetPresence(play)){
                    return false; 
                }
            }
            return true; 
        }

        int findOwner(Color* street){
            if (street == nullptr) return -1;
            for (int play = 1; play <= 4; play++){
                auto map = asset.find(play);
                if (map != asset.end()){
                    auto it = map -> second; 
                    auto itt = it.find(street);

                    if (itt != it.end()){
                        return play; 
                    }
                }
            }
            return -1; 
        }
    public: 
        Asset(){
            money = new Money();
            color = new Color();
        }
        Asset(Money* m, Color* c): money(m), color(c) {
            if (color != nullptr) {
                myMap = color -> colorMap();
                getAsset() = asset;
            } else {
                cerr << "Color object is null!" << endl;
            }
        }

        void updatedNameMap(map<int, string> &mapName);
        map<vector<Color*>, map<string, tuple<int, int, int>>> getMyMap() {return myMap;}
        // Asset(): money(nullptr), color(nullptr) {}
        void printAsset(){
            for (const auto player : asset){
                cout << "player " << player.first << ": ";
                for (const auto city: player.second){
                    cout << "The city name: " << city.first->getStreetName() << endl;
                    cout << "Properties's size: " << city.second.size() << endl; 
                }
                cout << endl; 
            }
        }

        map<int, map<Color*, vector<Properties*>>> getAsset() {
            return asset;
        }

        void buyAsset(Color* street, int player){
            if (street == nullptr || color == nullptr) {
                cerr << "Invalid pointer!" << endl;
                return;
            }

            string name = playerName[player];
            if (name.empty()) {cout << "Needed to check" << endl; } 
            cout << street -> getPrice() << ": street_value" << endl; 
            string response; 
            // figure out this logic later 
            // tuple<int, int, int> colorIn = color -> color_information(myMap, street -> getStreetName());
            int value = street -> getPrice(); 
            if ((street -> getStreetName() == "Community Chest")|| (street -> getStreetName() == "Go to Jail") || (street -> getStreetName() == "Free Parking") || (street -> getStreetName() == "Chance") || (street -> getStreetName() == "Go")){
                return; 
            }
            if ((!ownerVerification(street, player)) && (streetLookUp(street))){

                if (money -> getCash(player) >= value){
                    cin.ignore();
                    cout << name << ": Do you want to acquire this asset on "
                        << street -> getStreetName() << " street having the value of $"
                        << value << "? "; 
                    getline(cin, response);
                    lower_case(response);

                    if (response == "yes"){
                        money -> chargeIt(player, value);
                        // auto map = asset[player];
                        asset[player][street] = vector<Properties*> ();
                    } else {
                        cout << name << " chose not to buy" << endl; 
                    }
                } else if (money -> getCash(player) < value) {
                    cout << name << " does not have enough money to buy this asset." << endl; 
                }
            } else if ((!streetLookUp(street)) && (!ownerVerification(street, player))){
                value *= 2; 
                int own = findOwner(street);
                if (money -> getCash(player) >= value){
                    cin.ignore();
                    cout << name << ": Do you want to acquire this asset on "
                        << street -> getStreetName() << " street from player " << own << " which cost you $" 
                        << value << "? ";
                    getline(cin, response);
                    lower_case(response);

                    if (response == "yes"){
                        money -> chargeIt(player, value);
                        money -> sellIt(own, value);
                        auto old_owner = asset.find(own);

                        if (old_owner != asset.end()){
                            auto &map = old_owner -> second; 
                            auto old_properties = map.find(street);

                            if (old_properties != map.end()){
                                vector<Properties*> properties = old_properties -> second; 
                                properties.clear();
                                asset[player][street] = properties; 
                                map.erase(street);
                            }
                        }
                        cout << "Congratulations on " << name<< endl; 
                    }
                } else if (money -> getCash(player) < value) {
                    cout << "Not enough to acquire this asset " << endl; 
                }
            } else {
                cout << name << " does not have enough to acquire this asset" << endl; 
            }
        }

        int netWorth(int player){
            auto properties = asset.find(player);
            int total_properties = 0; 
            if (properties != asset.end()){
                auto &map = properties -> second; 
                for (auto itr = map.begin(); itr != map.end(); itr++){
                    Color* asst = itr -> first; 
                    total_properties += asst -> getPrice();
                }
            }
            int total_asset = money -> getCash(player) + total_properties; 
            return total_asset;
        }

        bool bankruptcy(Color* color, int player){
            int total_asset = netWorth(player);
            string name = playerName[player];
            if (findOwner(color) != -1){
                if (total_asset < color -> getRent()){
                    cout << name << " is bankrupt" << endl; 
                    return true; 
                } else {
                    return false; 
                }
            }
            
            return false; 
        }

        void eraseAsset(Color* color){
            int owner = findOwner(color);
            auto map = asset.find(owner);

            if (map != asset.end()){
                auto& it = map -> second; 
                auto properties = it.find(color);
                
                if (properties != it.end()){
                    properties -> second.clear();
                    it.erase(properties);
                }
            }
        }
        void cashDeduction(Money* money, int &amount_due, int player, int owner, int sellingAsset){
            
            money -> sellIt(player, sellingAsset);
            
            if (money -> getCash(player) >= amount_due) {
                money -> chargeIt(player, amount_due); 
                money -> sellIt(owner, amount_due);
                
                amount_due = 0; 
            }
        }
        void automaticSelling(int rent, int player, int owner){
            if (rent <= 0) {
                cout << rent << ": rent value in if-statement" << endl; 
                money -> sellIt(player, -rent); 
                rent = 0; 
                return;
            }
            auto findCheapestProperties = [&] (int play) -> Color*{
                auto map = asset.find(play);
                if (map != asset.end()){
                    auto& properties = map -> second; 
                    auto it = properties.begin();
                    Color* cheapest = it -> first; 
                    for (auto itr = properties.begin(); itr != properties.end(); itr++){
                        Color* asst = itr -> first; 
                        if (cheapest -> getPrice() > asst -> getPrice()){
                            cheapest = asst;
                        }
                    }
                    return cheapest; 
                }
                return nullptr; 
            }; 
            Color* cheapest = findCheapestProperties(player);
            int value = cheapest -> getPrice();

            cout << playerName[player] << " is selling " << cheapest -> getStreetName()
                << " with the price of $" << cheapest -> getPrice() << endl; 
            money -> sellIt(player, value);
            money -> sellIt(owner, rent);
            
            if (rent > money -> getCash(player)){
                automaticSelling(rent, player, owner);
            }
            else {
                money -> chargeIt(player, rent);
                rent = 0; 
            }
            eraseAsset(cheapest);
        }

        void manualSelling(int rent, int player, int owner){
            int cash = money -> getCash(player);
            int amount_due = rent - cash; 
            if (amount_due <= 0) { 
                money -> sellIt(player, -amount_due); 
                amount_due = 0; 
                return;
            }
            string response; 
            

            auto map = asset.find(player);

            if (map != asset.end()){
                auto& it = map -> second; 
                cin.ignore();


                while (amount_due > money -> getCash(player)){
                    bool assetSold = false; 
                    try {
                        for (auto itr = it.begin(); itr != it.end(); itr++){
                            Color* color = itr -> first; 
                            string street_name = color -> getStreetName();
                            int value = color -> getPrice();

                            cout << playerName[player] << ": ";
                            cout << "Your asset has " << street_name << " with the value of $"
                                << value << endl; 
                            
                            cout << "Do you want to sell this asset? ";
                            getline(cin, response);

                            if (response == "yes"){
                                cashDeduction(money, amount_due, player, owner, value);
                                eraseAsset(color);

                                assetSold = true; 
                                if (amount_due <= money -> getCash(player)){
                                    break; 
                                }
                            }
                        }

                        if ((!assetSold)){
                            throw invalid_argument("the amount due is still greater than your cash possession");
                        }
                    } catch(invalid_argument &e){
                        cout << endl; 
                        cout << "You still have to sell of your asset because "
                            << e.what() << endl; 
                        cout << endl; 
                    }
                }
                // while (amount_due > money -> getCash(player)){
                //         for (auto itr = it.begin(); itr != it.end(); itr++){
                //             Color* color = itr -> first; 
                //             string street_name = color -> getStreetName();
                            
                //             cout << "Your asset has " << street_name << " with the value of $"
                //                 << color -> getPrice() << endl; 
                    
                //             cout << "Do you want to sell this asset? ";
                //             getline(cin, response);
                //             lower_case(response);

                //             if (response == "yes"){
                //                 int value = color -> getPrice();
                        
                //                 cashDeduction(money, amount_due, player, owner, value); 
                //                 eraseAsset(color);
                //                 if (amount_due <= money -> getCash(player)){
                //                    break; 
                //                 }
                //             }    
                //         }
                        
                //             try {
                //                 if (amount_due <= money -> getCash(player)){
                //                     break; 
                //                 } else {
                //                     throw invalid_argument("the amount due is still greater than your cash possession");
                //                 }
                //             } catch (invalid_argument& e){
                //                 cout << endl; 
                //                 cout << "You still have to sell off your asset because " << e.what() << endl; 
                //                 cout << endl; 
                //             }   
                // }

            }
        }

    

        void sellAsset(Color* color, int player){
            string response; 
            int rent = color -> getRent();
            int cash = money -> getCash(player);
            int own = findOwner(color);
            
            string name = playerName[player];
            if((!ownerVerification(color, player)) && (!streetLookUp(color))){
                if (rent > cash){
                    if ((!bankruptcy(color, player))){
                        cin.ignore();
                        cout << "Your cash is less than your rent. Do you want us to automatically sell for you "
                            << " or you want to manually sell your asset? (a or b): ";
                        getline(cin, response);

                        if (response == "a"){
                            automaticSelling(rent, player, own);
                            buyAsset(color, player);
                        } else if (response == "b"){
                            manualSelling(rent, player, own);
                            buyAsset(color, player);
                        } 
                    } else {
                        cout << "You do not have enough money to pay rent" << endl; 
                    }
                } else if (cash >= rent) {
                    cout << "Charging " << name << " $" << rent << " for rent" << endl; 
                    money -> chargeIt(player, rent);
                    money -> sellIt(own, rent);
                    buyAsset(color, player);
                }
            } else if (streetLookUp(color)){
                buyAsset(color, player);
            }
            else {
                cout << "This is your asset" << endl; 
            }  
        }

        void playerAssetElimination(int player){
            auto outterMap = asset.find(player);
            
            if (outterMap != asset.end()){
                auto innerMap = outterMap -> second; 
                for (auto itr = innerMap.begin(); itr != innerMap.end(); itr++){
                    itr -> second.clear();
                    innerMap.erase(itr);
                }
            }
        }
        void mapUpdate(map<int, map<Color*, vector<Properties*>>> &myMap){
            asset = myMap; 
        }
        void modifiedMap(map<int, map<Color*, vector<Properties*>>> &myMap){
            myMap = asset; 
        }
        Money* getMoney() {return money;}
        Color* getColor() {return color;}
};
bool financialQualification(int value, int cash){
    if (value < cash){
        return true; 
    }
    return false;
}

class Upgrade: public Asset{
    private: 
        Asset* asst; 
        map<int, map<Color*, vector<Properties*>>> myMap;
        
        int maximum_houses = 4; 
        vector<Properties*> properties;   
        const double rent_rate = 1.1; 
        const double value_rate = 1.1; 
        const double cost_built_rate = 1.1; 

        void houseUpgrade(Color* color, int player){
            string response; 

            string player_name = playerName[player];
            int cost_built = color -> getCostBuilt();
            auto outterMap = myMap.find(player);
            if (outterMap != myMap.end()){
                auto innerMap = outterMap -> second; 
                auto it = innerMap.find(color);
                if (it != innerMap.end()){
                    properties = it -> second; 
                }
            }
            int properties_size = properties.size();
            properties.clear();
            cin.ignore();
            cout << player_name << ": ";
            cout << "Do you want to upgrade your asset to "
                << (properties_size + 1 == 1 ? "a house" : to_string(properties_size + 1) + " houses")
                << " on " << color -> getStreetName() << " street, which cost you $" << cost_built << "? "; 
            getline(cin, response);
            lower_case(response);

            if (response == "yes"){
                addProperties(asset, color, player, asst, this, money);
                valueAdjustment(color, player);
                // cout << "Debugging the properties.size() in the asset map: " << endl; 
                asst -> printAsset(); 
            }
        }

        void hotelUpgrade(Color* color, int player){
            string response; 
            string player_name = playerName[player];

            int cost_built = color -> getCostBuilt();
            cin.ignore();
            cout << player_name << ": ";
            cout << "Do you want to upgrade your asset to hotel on "
                << color -> getStreetName() << " street, which cost you $"
                << cost_built << "? ";
            getline(cin, response);
            lower_case(response);

            if (response == "yes"){
                addProperties(myMap, color, player, asst, this, money);
                valueAdjustment(color, player);
                asst -> printAsset();
            } else {
                cout << "You chose not to upgrade the hotel on " << color -> getStreetName()
                    << " street. " << endl;
            }
        }
        void valueAdjustment(Color* color, int player){
            int value = color -> getPrice();
            int rent = color -> getRent();
            int cost_built = color -> getCostBuilt();

            value *= value_rate; 
            rent *= rent_rate; 
            cost_built *= cost_built_rate;

            color -> priceAdjustment(value);
            color -> rentAdjustment(rent);
            color -> costBuiltAdjustment(cost_built);
        }
    public: 
        Upgrade(Asset* asset) : Asset(asset -> getMoney(), asset-> getColor()), asst(asset) {
            if (asset != nullptr){ 
                myMap = asst -> getAsset();
            } else {
                cout << "null pointer" << endl; 
            }
        }
        
        map<int, map<Color*, vector<Properties*>>> getMyMap() {return myMap;}
        void updateVector(const vector<Properties*>& prop){
            properties = prop; 
        }
        void mapChange(){
            myMap = asst -> getAsset();
            asset = myMap; 
        }
        void addProperties(map<int, map<Color*, vector<Properties*>>> &map_color, Color* color, int player, Asset* asset, Upgrade* upgrade, Money* money){
            auto map = map_color.find(player);
            string street_name = color -> getStreetName();

            int value = color -> getPrice();
            int rent = color -> getRent();
            int cost_built = color -> getCostBuilt();

            if (map != map_color.end()){
                auto it = map -> second; 
                auto prop = it.find(color);

                if (prop != it.end()){
                    vector<Properties*>& properties = prop -> second; 
                
                    if ((properties.size() < 4) && (financialQualification(cost_built, money -> getCash(player)))){
                        asst -> getMoney() -> chargeIt(player, cost_built);
                        House* house = new House(street_name, value, rent, cost_built);

                        properties.push_back(house);
                        upgrade -> updateVector(properties);
                        map_color[player][color] = properties;
                        asst -> mapUpdate(map_color);
                        properties.clear();
                    } else {
                        asst -> getMoney() -> chargeIt(player, cost_built); 
                        Hotel* hotel = new Hotel(street_name, value, rent, cost_built);

                        properties.clear();
                        prop -> second.clear();
                        properties.push_back(hotel);
                        updateVector(properties);
                        myMap[player][color] = properties; 
                        asst -> mapUpdate(myMap);
                        properties.clear();
                    }
                }
            }
        }

        void upgradeProperties(Color* color, int player){  
            mapChange();
            int cost_built = color -> getCostBuilt();
            int cash = money -> getCash(player);
            auto outterMap = myMap.find(player);
            if (outterMap != myMap.end()){
                auto innerMap = outterMap -> second; 
                auto it = innerMap.find(color);
                if (it != innerMap.end()){
                    properties = it -> second; 
                }
            }
            int properties_size = properties.size();
            properties.clear(); 
            if (ownerVerification(color, player)){
                if (financialQualification(cost_built, cash)){
                    if (properties.size() <= maximum_houses){
                        houseUpgrade(color, player);
                    } else {
                        hotelUpgrade(color, player);
                    }
                } else {
                    cout << "You do not have enough money to upgrade" << endl; 
                }
            } else {
                cout << "You do not own this asset. " << endl; 
            }   

        }
        
};

class UserBoard {
    private:  
        const int COL = 7; 
        const int ROW = 7; 
        void board_at_0_i_inputFile(vector<string>& board_at_0_i){
            ifstream inputFile("board_at_0_i.txt");
        
            if ((!inputFile.is_open())){
                cerr << "No file found: board_at_0_i.txt" << endl; 
                return; 
            }
            string line; 
            while(getline(inputFile, line)){
                board_at_0_i.push_back(line);
            }
            
            // cout << "Vector printed in the board_at_0_i file: ";
            // printVector(board_at_0_i);
            if (board_at_0_i.empty()){
                cout << "Empty vector. Needed to check the program" << endl;
                return;  
            }
            // cout << "Vector printed in the board_at_0_i file: ";
            // printVector(board_at_0_i); 
            inputFile.close();
        }

        // void board_at_i_9_inputFile(vector<string>& board_at_i_9){
        //     ifstream inputFile("board_at_i_9.txt");

        //     if((!inputFile.is_open())){
        //         cerr << "No file found: board_at_i_9.txt" << endl; 
        //         return; 
        //     }

        //     string line; 
        //     while(getline(inputFile, line)){
        //         board_at_i_9.push_back(line);
        //     }
        // }

        void board_at_i_9_inputFile(vector<string> &board_at_i_9){
            ifstream inputFile("board_at_i_9.txt");

            if((!inputFile.is_open())){
                cerr << "No file found: board_at_i_9.txt" << endl; 
                return; 
            }
            string line; 
            while(getline(inputFile, line)){
                board_at_i_9.push_back(line);
            }

            if (board_at_i_9.empty()){
                cout << "Empty vector. Needed to check the program" << endl; 
                return; 
            }
            // printVector(board_at_i_9);
            inputFile.close();
        }

        void board_at_9_i_inputFile(vector<string>& board_at_9_i){
            ifstream inputFile("board_at_9_i.txt");

            if((!inputFile.is_open())){
                cerr << "No file found: board_at_9_i.txt" << endl; 
                return; 
            }

            string line; 
            while(getline(inputFile, line)){
                // cout << line << ": line" << endl; 
                board_at_9_i.push_back(line);
            }

            if (board_at_9_i.empty()){
                cout << "Empty vector. Needed to check the program." << endl; 
                return; 
            }
            // printVector(board_at_9_i);
            inputFile.close();
        }

        void board_at_i_0_inputFile(vector<string>& board_at_i_0){
            ifstream inputFile("board_at_i_0.txt");

            if((!inputFile.is_open())){
                cerr << "No file found: board_at_i_0.txt" << endl; 
                return; 
            }
        
            string line; 
            while(getline(inputFile, line)){
                board_at_i_0.push_back(line);
            }

            if (board_at_i_0.empty()){
                cout << "Empty vector. Needed to check the program" << endl; 
                return; 
            }

            inputFile.close();
        }
        vector<vector<string>> user_board(){
            vector<vector<string>> user_monopoly_board(ROW, vector<string>(COL, "Empty"));
            
            vector<string> street;
        
            board_at_0_i_inputFile(street);

            if (street.empty()){
                cerr << "Empty vector" << endl; 
            }

            for (int col = 0; col < COL; col++){
                user_monopoly_board[0][col] = street[col];
            }
            street.clear();

            board_at_i_9_inputFile(street);
            
            if (street.empty()){
                cerr << "Empty vector" << endl; 
            }

            for (int row = 0; row < ROW; row++){
                user_monopoly_board[row][0] = street[row];
            }

            street.clear();

            board_at_9_i_inputFile(street);

            if (street.empty()){
                cerr << "Empty vector." << endl; 
            }

            for (int col = 0; col < COL; col++){
                user_monopoly_board[ROW - 1][col] = street[col];
            }

            street.clear();

            board_at_i_0_inputFile(street);

            if (street.empty()){
                cerr << "Empty vector." << endl; 
            }
            for (int row = 0; row < ROW; row++){
                user_monopoly_board[row][COL - 1] = street[row];
            }

            street.clear();

            return user_monopoly_board;
        }

        void printVector(vector<string> &sample_vector) const{
            for (int i = 0; i < sample_vector.size(); i++){
                cout << sample_vector[i] << " ";
            }
            sample_vector.clear();
            cout << endl; 
        }
    public:
        void printBoard(){
            vector<vector<string>> user = user_board();

            const int width = 15; 

            for (int row = 0; row < ROW; row++){

                if (row == 0){
                    cout << "+";
                    for (int col = 0; col < COL; col++){
                        cout << string(width, '-') << "+";
                    }
                    cout << endl; 
                }

                cout << "|";
                for (int col = 0; col < COL; col++){
                    cout << setw(width) << user[row][col] << "|";
                }
                cout << endl; 

                cout << "+";
                for (int col = 0; col < COL; col++){
                    cout << string(width, '-') << "+";
                }
                cout << endl; 
            } 
        }

};

class CommunityChestCard { 
    private: 
        vector<string> community_chest_card;

        void cardInputFile(){
            ifstream inputFile;
            inputFile.open("community_chest_card.txt");

            if((!inputFile.is_open())){
                cerr << "No file found: community_chest_card.txt" << endl; 
                return; 
            }

            string line; 
            while(getline(inputFile, line)){
                community_chest_card.push_back(line);
            }

            if (community_chest_card.empty()){
                cout << "community_chest_card vector is empty" << endl; 
                return; 
            }

            inputFile.close();
        }
        
        void printVector(){
            for (int i = 0; i < community_chest_card.size(); i++){
                cout << community_chest_card[i] << endl; 
            }
        }

    public: 
        CommunityChestCard() {
            cardInputFile();
        }
        vector<string> getCommunityChestCard() {return community_chest_card;}
};
class Virtual_Monopoly_Board {
    private: 
        Asset* asset; 
        Upgrade* upgrade;
        Money* money; 
        Color* color; 
        UserBoard userboard; 
        CommunityChestCard community_chest_card;
        random_device rd; 
        mt19937 gen; 

        int bailing_out_fee = 50; 
        map<int, int> jailCount; 
        int initializePosition; 
        int group_size = 2;
        string free_jail_card = "Jail Card";

        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap; 
        map<int, map<Color*, vector<Properties*>>> myAsset;
        map<int, int> mapIndex;
        map<int, string> playerName; 
        map<int, Color*> positionMap; 
        map<int, string> jailCard; 
        map<int, int> bankruptcy; 
        vector<string> city_name;

        void checkPosition(int player, const string& street_name){ 
            for (const auto& outerPair : myMap) {
                auto& map = outerPair.second; 
                for (size_t index = 0; index < outerPair.first.size(); index++){
                    auto it = map.find(street_name);
                    if ((it != map.end()) && (outerPair.first[index] -> getStreetName() == street_name)) {
                        positionMap[player] = outerPair.first[index];
                        return;  
                    }
                }
            }
            cout << "Street not found in map." << endl; 
        }
        void positionInitialization(){
            for (int i = 1; i <= 4; i++){
                positionMap[i] = color;
                // cout << "Player " << i << " is initialized at " << color -> getStreetName() << endl;
                for (size_t index = 0; index < city_name.size(); index++){
                    if (color -> getStreetName() == city_name[index]){
                        initializePosition = index;
                        city_name[initializePosition];
                        // cout << city_name[initializePosition] << ": city_name[intial Position]" << endl;
                        // cout << initializePosition << ": initial position" << endl; 
                        break; 
                    }
                }
            }
            
             
            for (int i = 1; i<= 4; i++){
                mapIndex[i] = initializePosition;
            }
        }

        int random_number(int begin, int end){
            uniform_int_distribution<>dis(begin, end);
            int rand = dis(gen);
            return rand;
        }

        int throwingDice(){
            int number = random_number(1, 6);
            return number; 
        }

        bool checkIndex(int index){
            return index >= 0 && index < 27; 
        }

        void update_color_map(int player, const string &street_name){
            checkPosition(player, street_name);
        }

        void update_city_name_vector(const int &updated_position, int player){
            int trial_index = mapIndex[player];  
            string street_name;  
            trial_index += updated_position;
            if (checkIndex(trial_index)){
                // cout << trial_index << ": trial index after adding" << endl;  
                mapIndex[player] = trial_index; 
                // cout << mapIndex[player] << " after updating in the mapIndex " << endl;

                street_name = city_name[mapIndex[player]];
                cout << playerName[player] << " is at " << street_name << endl; 
                if (jailCheck(player)){
                    jailCount[player]; 
                }
                // cout << city_name[mapIndex[player]] << ": city_name when index is there" << endl; 
                // cout << endl; 

                update_color_map(player, street_name);
                cout << endl; 
            } else { 
                int remaining_number = trial_index - 27; 
                // cout << remaining_number << ": trial index after subtracting" << endl; 
                mapIndex[player] = remaining_number; 

                street_name = city_name[mapIndex[player]];
                // cout << city_name[mapIndex[player]] << ": city_name when index is there" << endl;
                // cout << endl; 
                cout << playerName[player] << " is at " << street_name << endl; 
                update_color_map(player, street_name);
                asset -> getMoney() -> passGo(player);      
                cout << endl;      
            }   
        }

        bool checkJailFreeCardPossession(int player){
            if (jailCard[player].empty()){
                return false; 
            }
            return true; 
        }

        bool jailCheck(int player){
            Color* city = positionMap[player];
            string position_city_name = city -> getStreetName();

            if (position_city_name != "Go to Jail"){
                return false; 
            }
            return true; 
        }

        bool firstTimeInJail(int player){
            if (jailCount[player]== 1){
                return true; 
            }
            return false; 
        }
        bool jailCondition(int player){
            int user_choice; 

            if(checkJailFreeCardPossession(player)){
                cout << playerName[player] << " has " << free_jail_card
                    << ". You will get out of jail now without any charge." << endl; 
                
                jailCard.erase(player);

                auto it = jailCard.find(player);

                if (it != jailCard.end()){
                    cout << "Check the system regarding to checkJailFreeCardPossession in class Virtual Monopoly Board" << endl; 
                }
                return true; 
            }   

            // if (firstTimeInJail(player)) {cout << "True first tiem in jail" << endl;}
            // else {cout << "False" << endl; }
            if (firstTimeInJail(player)){
                cout << "Wait till next draw" << endl;
                // jailCount[player] = 0; 
                return false; 
            }

            do {
                cout << playerName[player]; 
                cout << ". You are in Jail now. You have two options: "
                    << "(1) Rolling Double or (2) Rolling two dices having value greater than 7. "
                    << "Please choose (1) or (2): ";
                cin >> user_choice; 
                cin.ignore();
            } while ((user_choice != 1) && (user_choice != 2));

            int first_dice = throwingDice();
            cout << "Your first dice's value: " << first_dice << endl; 
            int second_dice = throwingDice();
            cout << "Your second dice's value: " << second_dice << endl; 

            if (user_choice == 1){
                if (first_dice == second_dice){
                    cout << "You are getting charged $" << bailing_out_fee << " for bailing you out" << endl;
                    asset -> getMoney() -> chargeIt(player, bailing_out_fee);
                    cout << "Congratulations. You are out of the jail" << endl; 
                    jailCount[player] = 0; 
                    return true; 
                } else {
                    cout << "Good luck in the next draw" << endl; 
                    return false; 
                }
            } else {
                if (first_dice + second_dice > 7){
                    cout << "You are getting charged $" << bailing_out_fee << " for bailing you out" << endl;
                    asset -> getMoney() -> chargeIt(player, bailing_out_fee);
                    cout << "Congratulations. You are out of the jail" << endl; 
                    jailCount[player] = 0;
                    return true;  
                } else {
                    cout << "Good luck in the next draw" << endl; 
                    return false;
                }
            }
        }

        void throwingDiceForStep(int player){
            int first_dice = throwingDice();
            cout << "Your first dice's value: " << first_dice << endl;  
            int second_dice = throwingDice();
            cout << "Your second dice' value: " << second_dice << endl; 
            
            int total_steps = first_dice + second_dice;     
            cout << "Your total step in this turn is " << total_steps << endl; 
            update_city_name_vector(total_steps, player);
            
        }   

        bool checkVoidAsset(Color* color){
            myAsset = asset -> getAsset();
            // asset -> printAsset();
            if (myAsset.empty()){
                cout << "Empty myAsset map" << endl;
            }

            for (auto outerPair : myAsset){
                for (auto innerPair : outerPair.second){
                    auto mapIt = outerPair.second.find(innerPair.first);
                    if (mapIt != outerPair.second.end()){
                        return false; 
                    }
                }
            }
            return true; 
        }

        bool ownerVerification(Color* color, int player){
            auto mapIt = myAsset.find(player);

            if (mapIt != myAsset.end()){
                auto& it = mapIt -> second;
                auto findStreet = it.find(color);

                if (findStreet != it.end()){
                    return true;
                }
            }
            return false; 
        }

        void guideline(){
            vector<string> stringGuideLine; 
            ifstream inputFile; 
            inputFile.open("guidelines.txt");

            if ((!inputFile.is_open())){
                cerr << "No file found: guidelines.txt" << endl; 
                return; 
            }

            string line; 
            while(getline(inputFile, line)){
                stringGuideLine.push_back(line);
            }

            inputFile.close();

            for (int guide_line = 0; guide_line < stringGuideLine.size(); guide_line++){
                cout << stringGuideLine[guide_line] << endl; 
            }
            cout << endl;
        }

        bool gameContinuousQualification(){
            int total_bankrupted_players = 0; 

            for (int player = 1; player <= group_size; player++){
                Color* street = positionMap[player];
                cout << street -> getStreetName() << ": street name" << endl; 
                // if ((street =nullptr)){   
                //     continue; 
                // }
                if (playerName[player].empty()){
                    continue;
                }
                if(asset -> bankruptcy(street, player)){
                    cout << street -> getRent() << ": rent value at " << street -> getStreetName() << endl; 
                    total_bankrupted_players++; 
                    positionMap.erase(player);
                    playerName.erase(player);
                    asset -> playerAssetElimination(player);
                    group_size--; 
                    if (group_size == 1){
                        return false; 
                    }  
                }
                
            }
            
            return true; 
        }

        Color* findStreetCharacterstics(const string& street_name){
            for (auto itr = myMap.begin(); itr != myMap.end(); itr++){
                auto mapIt = itr -> second; 
                auto it = mapIt.find(street_name);

                if (it != mapIt.end()){
                    vector<Color*> color = itr -> first; 
                    for (Color* street : color){
                        if (street -> getStreetName() == street_name){
                            return street; 
                        }
                    }
                }
            }
            return nullptr; 
        }
public: 
        string community_chest_card_draw(){
            vector<string> community_card = community_chest_card.getCommunityChestCard();
            shuffle(community_card.begin(), community_card.end(), gen);

            return community_card[0];
        }

        bool AdvanceToGoCondition(const string& card, int player){
            if (card == "Advance to Go (Collect $200)"){
                string street_name = "Go";
                Color* street = findStreetCharacterstics(street_name);

                positionMap[player] = street;
                asset -> getMoney() -> passGo(player); 
                return true; 
            }
            return false;    
        }

        bool BankError(const string& card, int player){
            if (card == "Bank error in your favor. Collect $200"){ 
                int bank_compensation = 200; 
                asset -> getMoney() -> sellIt(player, bank_compensation);
                return true; 
            }
            return false; 
        }
        bool DoctorVisit(const string& card, int player){
            if (card == "Doctor's fee. Pay $50"){
                int doctor_fee = 50; 
                asset -> getMoney() -> chargeIt(player, doctor_fee);
                return true; 
            }
            return false; 
        }

        bool StockSale(const string& card, int player){
            if (card == "From sale of stock you get $50"){
                int stock_sale = 50; 
                asset -> getMoney() -> sellIt(player, stock_sale); 
                return true; 
            }
            return false; 
        }

        bool FreeGettingOutOfJail(const string& card, int player){
            if (card == "Get Out of Jail Free"){
                jailCard[player] = free_jail_card;
                return true; 
            }

            return false; 
        }

        bool GoToJail(const string& card, int player){
            if (card == "Go to Jail. Go directly to jail. Do not pass Go, do not collect $200"){
                string street_name = "Go to Jail";
                Color* street = findStreetCharacterstics(street_name);
                positionMap[player] = street; 

                return true; 
            }
            return false; 
        }
        
        bool HolidayFund(const string& card, int player){
            if (card == "Holiday fund matures. Receive $100"){
                int holiday_fund = 100; 
                asset -> getMoney() -> sellIt(player, holiday_fund);
                return true; 
            }
            return false; 
        }

        bool IncomeTaxRefund(const string& card, int player){
            if (card == "Income tax refund. Collect $20") {
                int income_tax_refund = 20; 
                asset -> getMoney() -> sellIt(player, income_tax_refund);
                return true; 
            }
            return false; 
        }

        bool BirthDayGift(const string& card, int player){
            int birthday_gift = 10; 
            if (card == "It is your birthday. Collect $10 from every player"){
                for (int individual = 1; individual <= group_size; individual++){
                    if (individual == player){
                        continue; 
                    }
                    asset -> getMoney() -> chargeIt(individual, birthday_gift);
                    asset -> getMoney() -> sellIt(player, birthday_gift); 
                }
                return true; 
            }
            return false; 
        }

        bool LifeInsurance(const string& card, int player){
            int life_insurance = 100; 
            if (card == "Life insurance matures. Collect $100"){
                asset -> getMoney() -> sellIt(player, life_insurance);
                return true; 
            }
            return false;
        }

        bool HospitalFee(const string& card, int player){
            int hospital_fee = 50; 
            if (card == "Pay hospital fees of $100"){
                asset -> getMoney() -> chargeIt(player, hospital_fee);
                return true; 
            }
            return false; 
        }

        bool ConsultationFee(const string& card, int player){
            int consultation_fee = 25; 
            if (card == "Receive $25 consultancy fee"){
                asset -> getMoney() -> sellIt(player, consultation_fee);
                return true; 
            }
            return false; 
        }

        bool SchoolFees(const string& card, int player){
            int school_fee = 50; 
            if (card == "Pay school fees of $50"){
                asset -> getMoney() -> chargeIt(player, school_fee);
                return true; 
            }
            return false; 
        }

        int chargeCost(int player) {
            int house_cost = 40; 
            int hotel_cost = 115; 
            int total_prop = 0; 
            int total_cost = 0; 
            auto mapIt = myAsset.find(player);
            if (mapIt != myAsset.end()){
                auto it = mapIt -> second;  
                for (auto itr = it.begin(); itr != it.end(); itr++){
                    Color* color = itr -> first; 
                    vector<Properties*> prop = itr -> second; 
                    for (Properties* property : prop){
                        total_prop++; 
                    }

                    if (total_prop == 1){
                        House* house = new House(color -> getStreetName(), color -> getPrice(), color -> getRent(), color -> getCostBuilt());
                        for (Properties* property : prop){
                            if (house == property){
                                total_cost += house_cost * total_prop; 
                                total_prop = 0; 
                            } else {
                                total_cost += hotel_cost * total_prop; 
                                total_prop = 0; 
                            }
                        }
                    } else {
                        total_cost += house_cost * total_prop; 
                        total_prop = 0; 
                    }
                }
            }
            cout << total_cost << ": total_cost" << endl; 
            return total_cost; 
        }

        bool StreetRepair(const string &card, int player){
            if (card == "You are assessed for street repair. $40 per house. $115 per hotel"){
                int total_repair_cost = chargeCost(player);
                asset -> getMoney() -> chargeIt(player, total_repair_cost);
                return true; 
            }
            return false; 
        }

        bool BeautyContest(const string &card, int player){
            int second_prize = 10; 
            if (card == "You have won second prize in a beauty contest. Collect $10"){
                asset -> getMoney() -> sellIt(player, second_prize);
                return true; 
            }

            return false; 
        }

        bool MoneyInheritance(const string& card, int player){
            int inheritance_money = 100; 
            if (card == "You inherit $100"){
                asset -> getMoney() -> sellIt(player, inheritance_money);
                return true;
            }
            return false; 
        }
        void community_chest_card_move(int player){
            string drawn_community_card = community_chest_card_draw();
            
            if (drawn_community_card.empty()){
                cout << "Check the function community_chest_card_draw()" << endl; 
                exit(0);
            }

            cout << drawn_community_card << ": card drawn" << endl; 

            cout << playerName[player] << "'s cash before drawing the card: "
                << asset -> getMoney() -> getCash(player) << endl; 
            if (AdvanceToGoCondition(drawn_community_card, player)){
                cout << playerName[player] << ": at " << positionMap[player] -> getStreetName() << endl; 
            } else if (BankError(drawn_community_card, player)){
                // No action needed, already handled in BankError Function. 
                cout << playerName[player] << "'s cash after the transaction: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (DoctorVisit(drawn_community_card, player)){
                // No action needed, already handled in DoctorVist Function. 
                cout << playerName[player] << "'s cash after the visit: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (StockSale(drawn_community_card, player)){
                // No action needed, already handled in StockSale Function. 
                cout << playerName[player] << "'s cash after selling your stock: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (FreeGettingOutOfJail(drawn_community_card, player)){
                cout << playerName[player] << " is drawn " << free_jail_card
                    << endl; 
            } else if (GoToJail(drawn_community_card, player)){
                cout << playerName[player] << ": You are in Jail now." << endl; 
            } else if(HolidayFund(drawn_community_card, player)){
                // No action needed, already handled in HolidayFund Function.
                cout << playerName[player] << "'s cash after receiving holiday fund: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (IncomeTaxRefund(drawn_community_card, player)){
                // No further action needed, already handled in IncomeTaxRefund Function. 
                cout << playerName[player] << "'s cash after receiving income tax refund: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (BirthDayGift(drawn_community_card, player)){ 
                cout << playerName[player] << "'s cash after receiving birthday " << ((group_size == 2) ? "gift" : "gifts") << " from other "
                     << ((group_size == 2) ? "player" : "players") << ": $" << asset -> getMoney() -> getCash(player) << endl; 
            } else if (LifeInsurance(drawn_community_card, player)){
                // No further action needed, already handled in LifeInsurance Function.
                cout << playerName[player] << "'s cash after receving life insurance money: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (HospitalFee(drawn_community_card, player)){
                // No futher action needed, already handled in HospitalFee Function
                cout << playerName[player] << "'s cash after paying hospital fee is "
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (ConsultationFee(drawn_community_card, player)){
                // No further action needed, alredy handled in Consultation Fee function. 
                cout << playerName[player] << "'s cash after receiving consultancy fee is "
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (SchoolFees(drawn_community_card, player)){
                // No further action needed, already handled in SchoolFees Function. 
                cout << playerName[player] << "' s cash after paying school fees: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (StreetRepair(drawn_community_card, player)){
                // No further action needed, already handled in StreetRepair Function. 
                cout << playerName[player] << "'s cash after paying street repair cost: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (BeautyContest(drawn_community_card, player)){
                // No further action needed, already handled in BeautyContest Funtion
                cout << playerName[player] << "'s cash after being rewarded second prize beauty contest: $"
                    << asset -> getMoney() -> getCash(player) << endl; 
            } else if (MoneyInheritance(drawn_community_card, player)){
                cout << playerName[player] << "'s cash after inheriting $100: $"
                    << asset -> getMoney() -> getCash(player) << endl;

            } else {
                cout << "Check the program. There is something off with the program" << endl; 
            }
        }

        bool checkCommunitiesChest(int player){
            Color* street = positionMap[player];
            int price = 0; 
            int rent = 0; 
            int cost_built = 0; 
            if (street -> getStreetName() == "Community Chest"){ 
                return true; 
            }
            
            return false;
        }

        bool checkFreeParking(int player){
            Color* street = positionMap[player];

            if (street -> getStreetName() == "Free Parking"){
                return true; 
            }
            return false; 
        }
    public:     
        Virtual_Monopoly_Board(): gen(rd()){
            money = nullptr; 
            color = nullptr; 
            
            try{
                asset = new Asset();
                upgrade = new Upgrade(asset);

                money = asset -> getMoney();
                color = asset -> getColor(); 

                // userboard.printBoard();

                city_name = color -> city_names();
                myAsset = asset -> getAsset();
                myMap = color -> colorMap();

                positionInitialization();
            } catch(const bad_alloc& e) {
                cerr << "Memory allocation failed" << e.what()<< endl; 
                if (asset) delete asset; 
                if (upgrade) delete upgrade;
                return; 
            }
        }
        
        ~Virtual_Monopoly_Board(){
            delete asset; 
            delete upgrade; 
        }
        
        map<int, string> getPlayerName() {return playerName;}
        
        void printVector(){
            cout << city_name.size() << ": city_name.size()" << endl; 
            for (int i = 0; i < city_name.size(); i++){
                cout << city_name[i] << " ";
            }
            cout << endl; 
        }

        Color* colorInTheMap(int player){
            return positionMap[player];
        }
        void playerMove(int player){
            string player_decision; 

            while(true){
                cout << playerName[player] << "'s turn. Please make your move: "
                    << "Please press (1) if you are ready for throwing the dices or press (q) to quit the program: "; 

                cin >> player_decision; 
                try {
                    if (player_decision == "1"){
                        cout << "Your dices are throwing...." << endl; 
                        break; 
                    } else if (player_decision == "q"){
                        cout << "Thank you for choosing us. Quitting the program..." << endl;
                        exit(0); 
                    } else {
                        throw invalid_argument("Invalid input"); 
                    }
                } catch(const invalid_argument& e) {
                    cout << "Error: " << e.what() << endl;                 
                }
            }
            
            cout << endl; 
            
            if (jailCheck(player)){
                if (jailCondition(player)){
                    throwingDiceForStep(player);
                } else {
                    cout << "You are in jail" << endl; 
                }
            } else {
                throwingDiceForStep(player);
                Color* street = colorInTheMap(player);
                if ((!checkCommunitiesChest(player)) && (!checkFreeParking(player))){
                    if ((checkVoidAsset(street))){
                        asset -> buyAsset(street, player); 
                        asset -> printAsset();
                        
                    } else { 
                        if ((ownerVerification(street, player))){
                            upgrade ->upgradeProperties(street, player);
                        } else {
                            asset -> sellAsset(street, player);
                            asset -> printAsset();
                        }
                   
                    }
                }  else if (checkCommunitiesChest(player)){
                    // Nothing more needed in this funciton. 
                    community_chest_card_move(player);
                } else if (checkFreeParking(player)){
                    cout << "You are at " << street -> getStreetName() << endl; 

                }   
  


                    
               

            }
            
        }
        
        void gameRegistration(){
            guideline();
            cout << endl; 
            string player_choice;  
            string player_name; 
            cout << "Welcome to our Monopoly_Like Board Game!" << endl;
            cout << "Before we start, my name is Henry Tran, and I'll be your host for this game." << endl;
            while (true){
                cout << "I would like to know how many people will be participating in this game. Please choose the number from 2 to 6: ";
                cin >> player_choice; 

                vector<int> number(5);
                iota(number.begin(), number.end(), 2);
                bool player_selection = false; 
                try {
                    for (int num = 2; num < number.size(); num++){
                       if (player_choice == to_string(num)){
                            cout << "In ready..." << endl; 
                            group_size = stoi(player_choice);
                            player_selection = true; 
                            break; 
                        }
                    }
                    
                    if ((!player_selection)){
                        throw invalid_argument("Invalid input");
                    } else {
                        break; 
                    }
                } catch(const invalid_argument& e){
                    cout << "Error: " << e.what() << endl; 
                }
            }
            string player_decision; 
            for (int player = 1; player <= group_size; player++){
                do {
                    cin.ignore();
                    cout << "Player " << player << ": Please let us know your name: ";
                    getline(cin, player_name); 
                    // cout << endl; 
                    cout << "Is it the name you would like to use in the game: " << player_name << "? (y/n)";
                    cin >> player_decision; 
                } while (player_decision != "y");
                playerName[player] = player_name; 
                asset -> updatedNameMap(playerName); 
                upgrade -> updatedNameMap(playerName);
            }
            for (auto itr = playerName.begin(); itr != playerName.end(); itr++){
                cout << itr -> first << ": player order" << endl; 
                cout << itr -> second << ": player's name" << endl; 
            }
        }

        void gameStart(){
            gameRegistration();
            while(gameContinuousQualification()){
                for (int player = 1; player <= group_size; player++){
                    userboard.printBoard();
                    playerMove(player);
                    printPlayerCash();
                }

            }
        }

        void printPlayerCash() const {
            for (int player = 1; player <= group_size; player++){
                cout << "Player " << player << "'s cash: " << asset -> getMoney() -> getCash(player) << endl; 
            }
        }
        void printMap() const {
            if (myMap.empty()) {
                cout << "null" << endl; 
            }
            for (const auto &group : myMap) {
                cout << "Group of Colors:" << endl;
                for (const auto &color : group.first) {
                    cout << "  - Street Name: " << color->getStreetName() << ", Price: $" << color->getPrice() 
                        << ", Rent: $" << color->getRent() << ", Cost to Build: $" << color->getCostBuilt() << endl;
                }   

                cout << "Color Information Map:" << endl;
                for (const auto &info : group.second) {
                    cout << "  Street Name: " << info.first << ", Price: $" << get<0>(info.second)
                        << ", Rent: $" << get<1>(info.second) << ", Cost to Build: $" << get<2>(info.second) << endl;
                }
            }
        }
};


void Asset:: updatedNameMap(map<int, string>& mapName){
    playerName = mapName; 
}

int main() {
    // // Initialize Money and Color objects
    // int player1 = 1;
    // Money* money = new Money();
    // int player2 = 2; 
    // cout << money->getCash(player2) << ": player 2's cash" << endl; 
    // cout << money->getCash(player1) << ": player 1's cash" << endl; 
   
    // // Initialize Color objects
    // string name = "Tokyo";
    // int price = 500;
    // int rent = 500;
    // int cost_built = 200;

    // string city_name = "Hanoi";
    // int price1 = 5000; 
    // int rent1 = 500; 
    // int cost_built1 = 2000; 
    // Color* color = new Color(name, price, rent, cost_built);

    // string city_name2 = "New York";
    // int price2 = 200; 
    // int rent2 = 200; 
    // int cost_built2 = 2100; 
    // color->initializeMap();

    // string city_name3 = "Toronto";
    // int price3 = 300; 
    // int rent3 = 100; 
    // int cost_built3 = 200; 

    // // print the user board
    // UserBoard userboard; 
    // userboard.printBoard();

    // // Initialize Asset object
    // Asset* asset1 = new Asset(money, color);
    
    // // Initialize Upgrade object
    // Upgrade* upgrade1 = new Upgrade(asset1);

    // // Create Color instances for properties
    // Color* color1 = new Color(name, price, rent, cost_built);
    // Color* color2 = new Color(city_name, price1, rent1, cost_built1);
    // Color* color3 = new Color(city_name2, price2, rent2, cost_built2);
    // Color* color4 = new Color(city_name3, price3, rent3, cost_built3);

    // // Buying and upgrading assets
    // asset1->buyAsset(color1, player1);
    // cout << "After buying asset..." << endl;
    // upgrade1->upgradeProperties(color1, player1);
    // cout << endl; 
    // upgrade1->upgradeProperties(color1, player1);
    // cout << endl; 
    // upgrade1->upgradeProperties(color1, player1);
    // cout << endl;
    // upgrade1->upgradeProperties(color1, player1);
    // cout << endl;
    // upgrade1->upgradeProperties(color1, player1);
    // cout << endl; 
    // asset1->buyAsset(color2, player2);
    // upgrade1->upgradeProperties(color2, player2);
    // asset1->sellAsset(color2, player1);

    // asset1->buyAsset(color3, player1);
    // asset1->sellAsset(color3, player2);

    // asset1->buyAsset(color4, player2);
    // asset1->sellAsset(color4, player1);

    // // Print asset status
    // asset1->printAsset();

    // // Display cash status
    // cout << money->getCash(player1) << ": player 1 cash after selling assets" << endl; 
    // cout << money->getCash(player2) << ": player 2 cash" << endl;
    Virtual_Monopoly_Board* virtual_board = new Virtual_Monopoly_Board(); 
    virtual_board->gameStart();
   
    // virtual_board -> playerMove(1);
    // virtual_board -> playerMove(2);
    // virtual_board -> playerMove(1);
    // virtual_board -> playerMove(1);
    // virtual_board -> playerMove(1);
    // virtual_board -> playerMove(1);
    // virtual_board -> playerMove(1);
    // virtual_board -> throwingDiceForStep(1); 
    // virtual_board -> throwingDiceForStep(1);
    // virtual_board -> throwingDiceForStep(1);
    // virtual_board -> throwingDiceForStep(1);
    // virtual_board -> throwingDiceForStep(1);

    // virtual_board -> throwingDice();
    // virutal_board.printVector();
    // // Clean up dynamically allocated memory
    // delete color; 
    // delete color1; 
    // delete color2; 
    // delete color3; 
    // delete color4; 
    // delete upgrade1;
    // delete asset1;
    // delete money;
    delete virtual_board;

    return 0;
}




