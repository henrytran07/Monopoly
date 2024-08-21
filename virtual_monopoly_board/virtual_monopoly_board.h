#ifndef VIRTUAL_MONOPOLY_BOARD_H
#define VIRTUAL_MONOPOLY_BOARD_H

#include <iostream> 
#include <vector> 
#include <random> 
#include <numeric> 
#include <tuple> 
#include "../money/money.h"
#include "../color_category/color_category.h"
#include "../assetFile/asset.h"
#include "..//userboard/MonopolyBoard.h"
#include "../community_chest_card/CommunityChestCard.h"

using namespace std; 

class Money; 
class Color; 
class Asset; 

class Properties; 
class House; 
class Hotel; 
class Upgrade; 
class CommunityChestCard; 
class Virtual_Monopoly_Board{
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
        int group_size; 
        string free_jail_card = "Jail Card";

        map<vector<Color*>, map<string, tuple<int, int, int>>> myMap;
        map<int, map<Color*, vector<Properties*>>> myAsset; 
        map<int, int> mapIndex; 
        map<int, string> playerName; 
        map<int, Color*> positionMap; 
        map<int, string> jailCard; 
        map<int, int> bankruptcy; 
        
        vector<string> city_name;
        
        void checkPosition(int player, const string& street_name);
        
        Color* findStreetCharacteristics(const string& street_name);
        
        int random_number(int begin, int end);
        int throwingDice();
        bool checkIndex(int index);

        void update_color_map(int player, const string& street_name);
        void update_city_name_vector(const int& updated_position, int player);
        bool checkJailFreeCardPossession(int player);
        bool jailCheck(int player);
        bool firstTimeInJail(int player);

        bool bailingOutAssessment(int bailing_out_fee, int player);
        bool jailCondition(int player);

        void throwDiceForStep(int player); 
        bool checkVoidAsset(Color* color);
        bool ownerVerification(Color* color, int player);

        void guideline();
        bool gameContinuousQualification();

        string community_chest_card_draw();
        bool AdvanceToGoCondition(const string& card, int player);
        bool BankError(const string& card, int player);
        bool DoctorVisit(const string& card, int player);
        bool StockSale(const string& card, int player);

        bool FreeGettingOutOfJail(const string& card, int player);
        bool GoToJail(const string& card, int player);
        bool HolidayFund(const string& card, int player);
        bool IncomeTaxRefund(const string& card, int player);
        bool BirthDayGift(const string& card, int player);

        bool LifeInsurance(const string& card, int player);
        bool HospitalFee(const string& card, int player);
        bool ConsultationFee(const string& card, int player);
        bool SchoolFees(const string& card, int player);
        int chargeCost(int player);

        bool StreetRepair(const string &card, int player);
        bool BeautyContest(const string &card, int player);
        bool MoneyInheritance(const string& card, int player);

        void community_chest_card_move(int player);

        bool checkCommunitiesChest(int player);
        bool checkFreeParking(int player);
        bool bankruptcyAssessment(Color* street, int player);
        void playerMove(int player);
        void gameRegistration();

        void printPlayerCash(); 
    public: 
        Virtual_Monopoly_Board();
        ~Virtual_Monopoly_Board();
        void positionInitialization();
        int getGroupSize() {return group_size;}
        string getPlayerName(int player) {return playerName[player];}
        Color* colorInTheMap(int player){ return positionMap[player];}
        void printColorMap();
        void gameStart();
        void updateMap(map<vector<Color*>, map<string, tuple<int, int, int>>> &colorMap);
};
#endif 