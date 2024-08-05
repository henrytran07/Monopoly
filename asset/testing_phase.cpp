#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> 
#include <fstream>
#include <iomanip>
#include <random> 
#include <tuple> 
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

        cash[1] = 350000; 
        cash[2] = 150000; 
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
        sellIt(player, 200);  // Assuming passing Go gives $200
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
    Color(): street_name(""), price(0), rent(0), cost_built(0){
        inputFile();
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

    void initializeValue() {
        index = 0;  // Start at 0 to avoid skipping the first city name
    }

    void resetValues(){
        p = 20000; 
        r = 1000; 
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

    vector<string> city_names() {return city_name;}   
    string getStreetName() const {return street_name;}
    int getPrice() const {return price;}
    int getRent() const {return rent;}
    int getCostBuilt() const {return cost_built;}
    void printVector() const {
        for (size_t i = 0; i < city_name.size(); i++) {
            cout << city_name[i] << ": city_name element." << endl;
        }
    }

    vector<Color*> BROWN() {
        vector<Color*> colors; 
        resetValues();
        for (int index = 0; index < 3; ++index){
            Color* city = new Color(city_name[index], p, r, cost); 
            cout << city->getStreetName() << ": city name" << endl; 
            colors.push_back(city);
        }
        return colors; 
    }

    vector<Color*> LIGHT_BLUE() {
        vector<Color*> colors; 
        resetValues();
        for (int index = 3; index < 9; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> PINK() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int index = 9; index < 12; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> ORANGE() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int index = 12; index < 15; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> RED() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int index = 15; index < 18; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> YELLOW() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int indec = 18; index < 21; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> GREEN() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int index = 21; index < 24; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    vector<Color*> DARK_BLUE() {
        vector<Color*> colors; 
        resetValues();
        marginalAddUp();
        for (int index = 24; index < 27; ++index){
            colors.push_back(new Color(city_name[index], p *= p_rate, r *= r_rate, cost *= cost_rate));
        }
        return colors;
    }

    map<vector<Color*>, map<string, tuple<int, int, int>>> Map(){
        map<vector<Color*>, map<string, tuple<int, int, int>>> mapCheck; 
        auto populateMap = [&] (const vector<Color*>& colorCategory){
            auto& map = mapCheck[colorCategory];

            for (const auto& color: colorCategory){
                map[color->street_name] = color->color();
                cout << "Adding: " << color->street_name << endl; 
            }
        };

        vector<Color*> pink_color = PINK();
        populateMap(pink_color);
        // for (auto color : pink_color) delete color;

        vector<Color*> orange_color = ORANGE();
        populateMap(orange_color);
        // for (auto color : orange_color) delete color;

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

class Asset {
    protected: 
        Money* money; 
        Color* color;
        map<int, map<Color*, vector<Properties*>>> asset; 
        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap ;
        Upgrade* upgrade; 

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



        bool search(Color* street){
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

        int Owner(Color* street){
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
                getAsset();
            } else {
                cerr << "Color object is null!" << endl;
            }
        }

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

        map<int, map<Color*, vector<Properties*>>> getAsset() {return asset;}

        void buyAsset(Color* street, int player){
            if (street == nullptr || color == nullptr) {
                cerr << "Invalid pointer!" << endl;
                return;
            }

            string response; 
            tuple<int, int, int> colorIn = color -> color_information(myMap, street -> getStreetName());
            int value = get<0> (colorIn);

            if (!ownerVerification(street, player) && search(street)){

                if (money -> getCash(player) >= value){
                    cout << "Player " << player << ": Do you want to acquire this asset on "
                        << street -> getStreetName() << " street having the value of $"
                        << value << "? "; 
                    getline(cin, response);
                    lower_case(response);

                    if (response == "yes"){
                        money -> chargeIt(player, value);
                        // auto map = asset[player];
                        asset[player][street] = vector<Properties*> ();
                    } else {
                        cout << "Player " << player << " chose not to buy" << endl; 
                    }
                } else {
                    cout << "Player " << player << " does not have enough money to buy this asset." << endl; 
                }
            } else if (!search(street) && !ownerVerification(street, player)){
                value *= 2; 
                int own = Owner(street);
                if (money -> getCash(player) >= value && own != -1){
                    cout << "Player " << player << ": Do you want to acquire this asset on "
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
                                asset[player][street] = old_properties -> second; 
                                old_properties -> second.clear();
                                map.erase(old_properties);
                            }
                        }
                        cout << "Congratulations on player " << player << endl; 
                    }
                } else {
                    cout << "Not enough to acquire this asset " << endl; 
                }
            } else {
                cout << "You do not have enough to acquire this asset" << endl; 
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
            if (total_asset < color -> getRent()){
                cout << "You are bankrupt." << endl; 
                return true; 
            }
            return false; 
        }

        void eraseAsset(Color* color){
            int owner = Owner(color);
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
      
            cout << amount_due << ": amount due " << endl; 
            
            money -> sellIt(player, sellingAsset);
            
            if (money -> getCash(player) >= amount_due) {
                money -> chargeIt(player, amount_due); 
                cout << money -> getCash(player) << ": getCash(player) " << endl; 
                money -> sellIt(owner, amount_due);
                cout << money -> getCash(owner) << ": getCash(owner)" << endl; 
                
                amount_due = 0; 
                cout << amount_due << ": amount_due" << endl; 
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
            cout << rent << ": rent value (I)" << endl; 
            Color* cheapest = findCheapestProperties(player);
            int value = cheapest -> getPrice();
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

                for (auto itr = it.begin(); itr != it.end(); itr++){
                    Color* color = itr -> first; 
                    string street_name = color -> getStreetName();

                    cout << rent << ": rent value" << endl;
                    cout << money -> getCash(player) << ": money -> getCash(player) " << endl;  
                    cout << "Your asset has " << street_name << " with the value of $"
                        << color -> getPrice() << endl; 

                    cout << "Do you want to sell this asset? ";
                    getline(cin, response);
                    lower_case(response);

                    if (response == "yes"){
                        int value = color -> getPrice();
                        
                        cashDeduction(money, amount_due, player, owner, value); 
                        eraseAsset(color);
                        if (amount_due > money -> getCash(player)){
                            manualSelling(rent, player, owner);
                        } else {
                            break; 
                        }
                    }
                }
            }
        }

    

        void sellAsset(Color* color, int player){
            string response; 
            int rent = color -> getRent();
            cout << rent << ": rent value of " << color -> getStreetName() << endl; 
            int cash = money -> getCash(player);
            int own = Owner(color);

            if (!ownerVerification(color, player)){
                        if ((rent > cash)){
                if ((!bankruptcy(color, player))){
                    cout << "Your cash is less than your rent. Do you want to us automatically sell for you "
                        << " or you want to manually sell your asset? (a or b)";
                    getline(cin, response);

                    if (response == "a"){
                        int cash = money -> getCash(player); 
                        if (cash >= rent){
                            money -> chargeIt(player, rent);
                            money -> sellIt(own, rent);
                        } else {
                            automaticSelling(rent, player, own);
                        }
                    } else if (response == "b"){
                        int cash = money -> getCash(player);
                        if (cash >= rent) {
                            money -> chargeIt(player, rent);
                            money -> sellIt(own, rent);
                        } else {
                            manualSelling(rent, player, own);
                        }
                    }

                } else {
                    cout << "You do not have enough money to pay rent. " << endl; 
                }
            } else if(search(color)) {
                cout << "This asset does not belong to anyone. " << endl; 
                buyAsset(color, player);
            } else {
                cout << "Charging player " << player << " $" << rent << " for rent" << endl; 
                money -> chargeIt(player, rent);
                money -> sellIt(own, rent);
                buyAsset(color, player);
            }
            } else {
                // Upgrade logic later. 
                cout << "this is your asset." << endl; 
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
        // Money* money; 
        // Color* color; 
        int maximum_houses = 4; 
        vector<Properties*> properties;   
        const double rent_rate = 1.1; 
        const double value_rate = 1.1; 
        const double cost_built_rate = 1.1; 
        friend class Asset; 

        void houseUpgrade(Color* color, int player){
            string response; 
            int cost_built = color -> getCostBuilt();
            int properties_size = properties.size();

            cout << "Do you want to upgrade your asset to "
                << (properties_size + 1 == 1 ? "a house" : to_string(properties_size + 1) + " houses")
                << " on " << color -> getStreetName() << " street, which cost you $" << cost_built << "? "; 
            getline(cin, response);
            lower_case(response);

            if (response == "yes"){
                addProperties(asset, color, player, asst, this, money);
                valueAdjustment(color, player);
                cout << "Debugging the properties.size() in the asset map: " << endl; 
                asst -> printAsset(); 
            }
        }

        void hotelUpgrade(Color* color, int player){
            string response; 
            int cost_built = color -> getCostBuilt();
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

            cout << color -> getPrice() << ": color -> getPrice() before changing" << endl;
            color -> priceAdjustment(value);
            cout << color -> getPrice() << ": color -> getPrice() after changing" << endl;
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
                        money -> chargeIt(player, cost_built);
                        House* house = new House(street_name, value, rent, cost_built);

                        properties.push_back(house);
                        upgrade -> updateVector(properties);
                        map_color[player][color] = properties;
                        asst -> mapUpdate(map_color);
                    } else {
                        money -> chargeIt(player, cost_built); 
                        Hotel* hotel = new Hotel(street_name, value, rent, cost_built);

                        properties.clear();
                        prop -> second.clear();
                        properties.push_back(hotel);
                        updateVector(properties);
                        myMap[player][color] = properties; 
                        asst -> mapUpdate(myMap);
                    }
                }
            }
        }

        void upgradeProperties(Color* color, int player){  
            mapChange();
            cout << "In upgrade Properties function: ";
            if (ownerVerification(color, player)) {cout << "True owner verification" << endl;}
            else {cout << "False verification" << endl;}
            int cost_built = color -> getCostBuilt();
            int cash = money -> getCash(player);
            if (ownerVerification(color, player)){
                if (financialQualification(cost_built, cash)){
                    if (properties.size() != maximum_houses){
                        cout << money -> getCash(player) << ": player's cash before house upgrade" << endl;
                        houseUpgrade(color, player);
                        cout << money -> getCash(player) << ": player's cash after house upgrade" << endl;  
                    } else {
                        hotelUpgrade(color, player);
                    }
                } else {
                    cout << "You do not have enough money to update" << endl; 
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

        void board_at_i_9_inputFile(vector<string>& board_at_9_i){
            ifstream inputFile("board_at_9_i.txt");

            if((!inputFile.is_open())){
                cerr << "No file found: board_at_9_i.txt" << endl; 
            return; 
            }

            string line; 
                while(getline(inputFile, line)){
                board_at_9_i.push_back(line);
            }
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
                board_at_9_i.push_back(line);
            }

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
            inputFile.close();
        }
        vector<vector<string>> user_board(){
            vector<vector<string>> user_monopoly_board(ROW, vector<string>(COL, ""));
            vector<string> street(COL);

            board_at_0_i_inputFile(street);
            for (int col = 0; col < COL; col++){
                user_monopoly_board[0][col] = street[col];
            }

            board_at_i_9_inputFile(street);
            for (int row = 0; row < ROW; row++){
                user_monopoly_board[row][0] = street[row];
            }

            board_at_9_i_inputFile(street);
            for (int col = 0; col < COL; col++){
                user_monopoly_board[6][col] = street[col];
            }

            board_at_i_0_inputFile(street);
            for (int row = 0; row < ROW; row++){
                user_monopoly_board[row][6] = street[row];
            }

            return user_monopoly_board;
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

class Virtual_Monopoly_Board{
    private: 
        Asset* asset; 
        Upgrade* upgrade;
        UserBoard userboard; 
        static random_device rd; 
        static mt19937 gen; 

        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap; 
        vector<string> city_name;
    public:     
        Virtual_Monopoly_Board(){
            Money* money = nullptr; 
            Color* color = nullptr; 
            try{
                asset = new Asset();
                money = asset -> getMoney();
                color = asset -> getColor();
                upgrade = new Upgrade(asset);

                userboard.printBoard();
                city_name = color -> city_names();
                myMap = asset -> getMyMap();
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
        void printVector(){
            cout << city_name.size() << ": city_name.size()" << endl; 
            for (int i = 0; i < city_name.size(); i++){
                cout << city_name[i] << " ";
            }
            cout << endl; 
        }
};
random_device Virtual_Monopoly_Board:: rd;
mt19937 Virtual_Monopoly_Board:: gen(rd());
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
 
    Virtual_Monopoly_Board virutal_board; 
    virutal_board.printVector();

    // // Clean up dynamically allocated memory
    // delete color; 
    // delete color1; 
    // delete color2; 
    // delete color3; 
    // delete color4; 
    // delete upgrade1;
    // delete asset1;
    // delete money;

    return 0;
}




