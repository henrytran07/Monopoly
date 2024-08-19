
#include "/Users/tranhuuloc/Documents/DSA_CODE/Monopoly/virtual_monopoly_board/virtual_monopoly_board.h"
#include <iostream> 
#include <fstream> 
#include <random> 
#include <numeric> 

using namespace std; 

Virtual_Monopoly_Board::Virtual_Monopoly_Board(): gen(rd()){
    money = nullptr; 
    color = nullptr; 

    try {
        asset = new Asset();
        upgrade = new Upgrade(asset);

        money = asset -> getMoney();
        color = asset -> getColor();

        city_name = color -> city_names();
        
        myAsset = asset -> getAsset();
        myMap = color -> colorMap();

        gameRegistration();
        positionInitialization();
    } catch(const bad_alloc& e){
        cerr << "Memory allocation failed " << e.what() << endl; 
        if (asset) delete asset; 
        if (upgrade) delete upgrade; 

        return; 
    }
}
        
Virtual_Monopoly_Board:: ~Virtual_Monopoly_Board(){
    delete asset; 
    delete upgrade; 
}

void Virtual_Monopoly_Board:: updateMap(map<vector<Color*>, map<string, tuple<int, int, int>>> &colorMap){
    myMap = colorMap; 
}
void Virtual_Monopoly_Board:: checkPosition(int player, const string& street_name){
    color -> mapUpdate(myMap);
    for (const auto& outerPair: myMap){
        auto& map = outerPair.second; 
        for (size_t index = 0; index < outerPair.first.size(); index++){
            auto it = map.find(street_name);
            if (it != map.end() && (outerPair.first[index] -> getStreetName() == street_name)){
                positionMap[player] = outerPair.first[index];
                return; 
            }
        }
    }
    cout << "Street not found in map" << endl; 
}

void Virtual_Monopoly_Board:: positionInitialization(){
    for (int player = 1; player <= group_size; player++){
        positionMap[player] = color; 
        for (size_t index = 0; index < city_name.size(); index++){
            if (color -> getStreetName() == city_name[index]){
                initializePosition = index; 
                city_name[initializePosition];
                break;
            }

        }
    }
    
    for (int player = 1; player <= group_size; player++){
        mapIndex[player] = initializePosition; 
    }
}

int Virtual_Monopoly_Board:: random_number(int begin, int end){
    uniform_int_distribution<> dis(begin, end);
    int randomNumber = dis(gen);

    return randomNumber; 
}

int Virtual_Monopoly_Board:: throwingDice(){
    int number = random_number(1, 6);
    return number; 
}

bool Virtual_Monopoly_Board:: checkIndex(int number){
    return number >= 0 && number < 27;
}

void Virtual_Monopoly_Board:: update_color_map(int player, const string& street_name){
    checkPosition(player, street_name);
}

void Virtual_Monopoly_Board:: update_city_name_vector(const int& updated_position, int player){
    int trial_index = mapIndex[player];
    string street_name; 
    trial_index+= updated_position;  
    if (checkIndex(trial_index)){
        mapIndex[player] = trial_index; 
        street_name = city_name[mapIndex[player]];
        cout << playerName[player] << " is at " << street_name << endl; 
        if (jailCheck(player)){
            jailCount[player]++;
        }

        update_color_map(player, street_name);
        cout << endl; 
    } else {
        int remaining_number = trial_index - 27; 
        mapIndex[player] = remaining_number; 

        street_name = city_name[mapIndex[player]];

        cout << playerName[player] << " is at " << street_name << endl; 
        update_color_map(player, street_name);
        asset -> getMoney() -> passGo(player);
        cout << endl; 
    }
}

bool Virtual_Monopoly_Board:: checkJailFreeCardPossession(int player){
    if (jailCard[player].empty()){
        return false; 
    }
    return true; 
}

bool Virtual_Monopoly_Board:: jailCheck(int player){
    Color* city = positionMap[player];

    if (city == nullptr){
        cout << "null city pointer!" << endl; 
        exit(0);
    }

    string position_city_name = city -> getStreetName();

    if (position_city_name != "Go to Jail"){
        return false; 
    }

    return true; 
}

bool Virtual_Monopoly_Board:: firstTimeInJail(int player){
    if (jailCount[player] == 1){
        return true; 
    }

    return false; 
}

bool Virtual_Monopoly_Board:: bailingOutAssessment(int bailing_out_fee, int player){
    string first_condition = "a";
    string second_condition = "b";
    if (bailing_out_fee <= asset -> getMoney() -> getCash(player)){
        cout << "You are getting charged $" << bailing_out_fee
            << " for bailing you out" << endl; 
        asset -> getMoney() -> chargeIt(player, bailing_out_fee);
        return true; 
    } else {
        if (bailing_out_fee > asset -> calculatingPlayerNetWorth(player)){
            cout << playerName[player] << " is bankrupt" << endl; 

            positionMap.erase(player);
            playerName.erase(player);

            asset -> getMoney() -> eraseMap(player);
            asset -> playerAssetElimination(player);

            group_size--; 
            return false; 
        } else {
            string response; 
            cout << "Do you want want us to automatically sell your asset or "
                 << "manually sell your asset (a or b): ";
            getline(cin, response);
            asset -> userHandleResponse(response, first_condition, second_condition);

            if (response == "a"){
                asset -> automaticSelling(bailing_out_fee, player, 0);
                cout << "You are getting charged $" << bailing_out_fee << " for bailing you out" << endl;
                return true; 
            } else {
                asset -> manualSelling(bailing_out_fee, player, 0, first_condition, second_condition);
                cout << "You are getting charged $" << bailing_out_fee << " for bailing you out" << endl;
                return true;
            }
        }
    }
}

bool Virtual_Monopoly_Board:: jailCondition(int player){
    if ((checkJailFreeCardPossession(player))){
        cout << playerName[player] << " has " << free_jail_card
            << ". You will get out of jail now without any charge." << endl; 
        jailCard.erase(player);

        auto it = jailCard.find(player);

        if (it != jailCard.end()){
            cout << "Check the system regarding to checkJailFreeCardPosession" << endl; 
        }
        return true; 
    }

    if (firstTimeInJail(player)){
        cout << "Wail till next draw " << endl; 
        return false; 
    }

    string user_choice; 
    string first_condition = "1";
    string second_condition = "2";
    do {
        cout << playerName[player] << ": "
            << " You are in jail now. You have two options: "
            << "(1) Rolling Double or (2) Rolling two dices having value greater than 7."
            << ". Please choose (1) or (2)";
            getline(cin, user_choice);
            asset -> userHandleResponse(user_choice, first_condition, second_condition);
            cout << endl; 
    } while ((user_choice != "1") && (user_choice != "2"));

    cout << "Throwind dices now..." << endl; 
    int first_dice = throwingDice();
    cout << "The first dice's value: " << first_dice << endl; 

    int second_dice = throwingDice();
    cout << "The second dice's value: " << second_dice << endl; 

    if (user_choice == "1"){
        if (first_dice == second_dice){
            if (bailingOutAssessment(bailing_out_fee, player)){
                cout << "Congratulations. " << playerName[player] << " is out of jail." <<endl; 
                jailCount[player] = 0; 
                cout << endl; 
                return true; 
            } else {
                /// Already resolved in the function. 
            }
        } else {
            cout << "Good luck in the next draw. " << endl; 
            cout << endl; 
            return false; 
        }
    } else {
        if (first_dice + second_dice > 7){
            if (bailingOutAssessment(bailing_out_fee, player)){
                cout << "Congraulations. " << playerName[player] << " is out of jail now" << endl; 
                jailCount[player] = 0; 
                cout << endl; 
                return true; 
            }
        } else {
            cout << "Good luck in the next draw. " << endl; 
            cout << endl; 
            return true; 
        }
    }

    return true; 
}
void Virtual_Monopoly_Board:: throwDiceForStep(int player){
    cout << "Dices are throwing..." << endl; 
    int first_dice = throwingDice();
    cout << "The first dice's value: " << first_dice << endl; 
    int second_dice = throwingDice();
    cout << "The second dice's value: " << second_dice << endl; 
    
    int total_steps = first_dice + second_dice;
    cout << "The total steps in your turn is " << total_steps << endl; 

    update_city_name_vector(total_steps, player);
}

bool Virtual_Monopoly_Board:: checkVoidAsset(Color* color){
    if (color == nullptr){
        cerr << "Null color pointer in checkVodiAsset function" << endl; 
        exit(1);
    }

    myAsset = asset -> getAsset();

    if (myAsset.empty()) {
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

bool Virtual_Monopoly_Board:: ownerVerification(Color* color, int player){
    auto mapIt = myAsset.find(player);

    if (mapIt != myAsset.end()){
        auto &it = mapIt -> second; 
        auto findStreet = it.find(color);

        if (findStreet != it.end()){
            return true;
        }
    }

    return false; 
}

void Virtual_Monopoly_Board:: guideline(){
    vector<string> stringGuideLine; 
    
    ifstream inputFile; 
    inputFile.open("virtual_monopoly_board/guidelines.txt");

    if ((!inputFile.is_open())){
        cerr << "No file found: guidelines.txt" << endl; 
        return; 
    }

    string line; 
    while (getline(inputFile, line)){
        stringGuideLine.push_back(line);
    }
    inputFile.close();

    if (stringGuideLine.empty()){
        cout << "Empty stringGuidLine vector..." << endl; 
    } else {
        for (int guide_line = 0; guide_line < stringGuideLine.size(); guide_line++){
            cout << stringGuideLine[guide_line] << endl; 
        }
        cout << endl; 
    }
}

bool Virtual_Monopoly_Board:: gameContinuousQualification(){
    if (group_size == 1){
        return false; 
    }

    return true; 
}

Color* Virtual_Monopoly_Board:: findStreetCharacteristics(const string& street_name){
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

string Virtual_Monopoly_Board::community_chest_card_draw(){
    vector<string> community_card = community_chest_card.getCommunityChestCard();
    shuffle(community_card.begin(), community_card.end(), gen);

    return community_card[0];
}
bool Virtual_Monopoly_Board:: AdvanceToGoCondition(const string& card, int player){
    if (card == "Advance to Go (Collect $200)"){
        string street_name = "Go";
        Color* street = findStreetCharacteristics(street_name);
        positionMap[player] = street;

        asset -> getMoney() -> passGo(player); 
        return true; 
    }

    return false;    
}

bool Virtual_Monopoly_Board:: BankError(const string& card, int player){
    if (card == "Bank error in your favor. Collect $200"){ 
        int bank_compensation = 200; 
        asset -> getMoney() -> sellIt(player, bank_compensation);
        return true; 
    }

    return false; 
}
bool Virtual_Monopoly_Board:: DoctorVisit(const string& card, int player){
    if (card == "Doctor's fee. Pay $50"){
        int doctor_fee = 50; 
        asset -> getMoney() -> chargeIt(player, doctor_fee);
        return true; 
    }
    
    return false; 

}

bool Virtual_Monopoly_Board:: StockSale(const string& card, int player){
    if (card == "From sale of stock you get $50"){
        int stock_sale = 50; 
        asset -> getMoney() -> sellIt(player, stock_sale); 
        return true; 
    }

    return false; 
}

bool Virtual_Monopoly_Board:: FreeGettingOutOfJail(const string& card, int player){
    if (card == "Get Out of Jail Free"){
        jailCard[player] = free_jail_card;
        return true; 
    
    }

    return false; 
}

bool Virtual_Monopoly_Board:: GoToJail(const string& card, int player){
    if (card == "Go to Jail. Go directly to jail. Do not pass Go, do not collect $200"){
        string street_name = "Go to Jail";
        Color* street = findStreetCharacteristics(street_name);
        positionMap[player] = street; 

        return true; 
    }
    
    return false; 
}
        
bool Virtual_Monopoly_Board:: HolidayFund(const string& card, int player){
    if (card == "Holiday fund matures. Receive $100"){
        int holiday_fund = 100; 
        asset -> getMoney() -> sellIt(player, holiday_fund);
        return true; 
    }

    return false; 
}

bool Virtual_Monopoly_Board:: IncomeTaxRefund(const string& card, int player){
    if (card == "Income tax refund. Collect $20") {
        int income_tax_refund = 20; 
        asset -> getMoney() -> sellIt(player, income_tax_refund);
        return true; 
    }
    
    return false; 
}

bool Virtual_Monopoly_Board:: BirthDayGift(const string& card, int player){
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

bool Virtual_Monopoly_Board:: LifeInsurance(const string& card, int player){
    int life_insurance = 100; 
    
    if (card == "Life insurance matures. Collect $100"){
        asset -> getMoney() -> sellIt(player, life_insurance);
        return true; 
    }
    
    return false;
}

bool Virtual_Monopoly_Board:: HospitalFee(const string& card, int player){
    int hospital_fee = 50; 
    
    if (card == "Pay hospital fees of $100"){
        asset -> getMoney() -> chargeIt(player, hospital_fee);
        return true; 
    }
    
    return false; 
}

bool Virtual_Monopoly_Board:: ConsultationFee(const string& card, int player){
    int consultation_fee = 25; 
    
    if (card == "Receive $25 consultancy fee"){
        asset -> getMoney() -> sellIt(player, consultation_fee);
        return true; 
    }
    return false; 
}

bool Virtual_Monopoly_Board:: SchoolFees(const string& card, int player){
    int school_fee = 50; 
    
    if (card == "Pay school fees of $50"){
        asset -> getMoney() -> chargeIt(player, school_fee);
        return true; 
    }
    
    return false; 
}

int Virtual_Monopoly_Board:: chargeCost(int player) {
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

                delete house; 
            } else {
                total_cost += house_cost * total_prop; 
                total_prop = 0; 
            }
        }
    }
    
    cout << total_cost << ": total_cost" << endl; 
    return total_cost; 
}

bool Virtual_Monopoly_Board:: StreetRepair(const string &card, int player){
    if (card == "You are assessed for street repair. $40 per house. $115 per hotel"){
        int total_repair_cost = chargeCost(player);
        asset -> getMoney() -> chargeIt(player, total_repair_cost);
        return true; 
    }
    
    return false; 
}

bool Virtual_Monopoly_Board:: BeautyContest(const string &card, int player){
    int second_prize = 10; 
    
    if (card == "You have won second prize in a beauty contest. Collect $10"){
        asset -> getMoney() -> sellIt(player, second_prize);
        return true; 
    }

    return false; 
}

bool Virtual_Monopoly_Board:: MoneyInheritance(const string& card, int player){
    int inheritance_money = 100; 
    
    if (card == "You inherit $100"){
        asset -> getMoney() -> sellIt(player, inheritance_money);
        return true;
    }
    
    return false; 
}
void Virtual_Monopoly_Board:: community_chest_card_move(int player){
    string drawn_community_card = community_chest_card_draw();
            
    if (drawn_community_card.empty()){
        cout << "Check the function community_chest_card_draw()" << endl; 
        exit(0);
    }

    cout << playerName[player] << " is drawing " << drawn_community_card << endl; 

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

bool Virtual_Monopoly_Board:: checkCommunitiesChest(int player){
    Color* street = positionMap[player];
    int price = 0; 
    int rent = 0; 
    int cost_built = 0; 

    if (street -> getStreetName() == "Community Chest"){ 
        return true; 
    }
            
    return false;
}

bool Virtual_Monopoly_Board:: checkFreeParking(int player){
    Color* street = positionMap[player];

    if (street -> getStreetName() == "Free Parking"){
        return true; 
    }
    return false; 
}

bool Virtual_Monopoly_Board:: bankruptcyAssessment(Color* street, int player){
    if (playerName[player].empty()){
        return true; 
    }

    if ((asset -> bankruptcy(street, player))){
        cout << street -> getRent() << ": rent value at "
            << street -> getStreetName() << endl; 
        positionMap[player];
        playerName.erase(player);
        asset -> playerAssetElimination(player);

        group_size --; 
        return true; 
    }

    return false; 
}

void Virtual_Monopoly_Board:: playerMove(int player){
    string player_decision ; 

    while(true){
        cout << playerName[player] << "'s turn: Please make your move: "
            << "Pressing (1) if you are ready for throwing dices, "
            << " or choosing (q) to quit the program: ";
        getline(cin, player_decision);

        try {
            if (player_decision == "1"){
                cout << "The dices are throwing..." << endl; 
                break; 
            } else if (player_decision == "q"){
                cout << "Thank you for choosing us. Quitting the program...";
                exit(0);
            } else {
                throw invalid_argument("Invalid Input.");
            }
        } catch (const invalid_argument& e){
            cout << "Error: " << e.what() << endl; 
        }
    }
    cout << endl; 

    if (jailCheck(player)){
        if (jailCondition(player)){
            throwDiceForStep(player);
        } else {
            cout << playerName[player] << ": You are in jail..." << endl; 

        }
    } else {
        throwDiceForStep(player);
        Color* street = colorInTheMap(player); 
        if ((!checkCommunitiesChest(player)) && (!checkFreeParking(player))){
            if (checkVoidAsset(street)){
                asset -> buyAsset(street, player);
                cout << endl; 
                asset -> printAsset();
                cout << endl; 
            } else {
                if ((!bankruptcyAssessment(street, player))){
                    if ((ownerVerification(street, player))){
                        upgrade -> upgradeProperties(street, player);
                    } else {
                        asset -> sellAsset(street, player);
                        cout << endl; 
                        asset -> printAsset();
                        cout << endl; 
                    }
                } else {
                    // No further statement for now.
                }
            }
        } else if (checkCommunitiesChest(player)){
            community_chest_card_move(player);
        } else if (checkFreeParking(player)){
            cout << playerName[player] << ": You are at " << street -> getStreetName() << endl; 
        }
    }
}

void Virtual_Monopoly_Board:: gameRegistration(){
    guideline();
    cout << endl; 

    string player_choice; 
    string player_name; 
    string player_decision; 

    cout << "Welcome to our Monopoly_Like Board Game!" << endl; 
    cout << "Before we start, my name is Henry Tran, and I'll be your host for this game" << endl; 
    cout << endl; 

    while(true){
        cout << "I would like to know how many people will be participating in this game. "
            << "Please choose the number from 2 to 6: ";
        getline(cin, player_choice); 
        cout << endl; 

        vector<int> number(5);
        iota(number.begin(), number.end(), 2);
        bool player_selection = false; 

        try {
            for (int num = 2; num < number.size(); num++){
                if (player_choice == to_string(num)){
                    cout << "In ready... " << endl; 

                    group_size = stoi(player_choice);
                    player_selection = true; 
                    break; 
                }
            }

            if (!player_selection){
                throw invalid_argument("Invalid input");
            } else {
                break; 
            }
        } catch (const invalid_argument& e){
            cout << "Error: " << e.what() << endl; 
        }
    }

    for (int player = 1; player <= group_size; player++){
        do {
            cout << "Player " << player << ": Please let us know your name: ";
            getline(cin, player_name);

            cout << "Is it the name you would like to use in the game? (y/n): " << player_name << ": ";
            getline(cin, player_decision);
        }  while (player_decision != "y");
        cout << endl; 

        playerName[player] = player_name; 
        asset -> updatedNameMap(playerName);
        upgrade -> updatedNameMap(playerName);
        money -> updatedNameMap(playerName);
    }


}

void Virtual_Monopoly_Board:: printPlayerCash() {
    for (int player = 1; player <= group_size; player++){
        cout << playerName[player] << "'s cash: $" << asset -> getMoney() -> getCash(player) << endl; 
    }
}
void Virtual_Monopoly_Board:: gameStart(){

    while (gameContinuousQualification()){
        for (int player = 1; player <= group_size; player++){
            userboard.printBoard();
            playerMove(player);
            printPlayerCash();
        }
    }
}

void Virtual_Monopoly_Board:: printColorMap(){

    if (myMap.empty()){
        cout << "Empty myMap" << endl; 
        return; 
    }

    for (auto outerPair: myMap){
        vector<Color*> color = outerPair.first; 

        for (Color* street : color){
            cout << street -> getStreetName() << ": street name" << endl; 
        }
    }
}
