//
// Created by shlom on 09/06/2022.
//

//
// Created by shlom on 09/06/2022.
//
#include "Merchant.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::cin;
using std::cout;
using std::getline;
bool checkNumber(string str);
const int BUY_NOTHING =0;
const int BUY_HP = 1;
const int BUY_BUFF = 2;
const int PRICE_HP = 5;
const int PRICE_BUFF = 10;
const int MERCHANT_HEAL = 1;
const int MERCHANT_BUFF = 1;
const int NOT_ENOUGH_MONEY = 0;
const int NUM_OF_CHOICES = 3;
const char LINEBREAK = '\n';



Merchant::Merchant():
        Card(CardType::NoBattle, CardStats(IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT), "Merchant")
{}

void Merchant::applyEncounter(Player &player) const {
    string strChoice;
    int numChoice=NUM_OF_CHOICES+1;
    bool flag = false;
    printMerchantInitialMessageForInteractiveEncounter(cout, player.getName(), player.get_money());
    while (true) {
        getline(cin, strChoice, LINEBREAK);
        flag = checkNumber(strChoice);
        if (flag && strChoice.length()<2 && strChoice.length()>0) {
            numChoice = std::stoi(strChoice);
            if (numChoice < NUM_OF_CHOICES && numChoice >= 0) {
                flag = true;
                break;
            }
        }
        printInvalidInput();
    }

    if (flag) {
        int price;
        switch (numChoice) {
            case BUY_NOTHING:
                price = BUY_NOTHING;
                break;
            case BUY_HP:
                if (player.pay(PRICE_HP)) {
                    player.heal(MERCHANT_HEAL);
                    price = PRICE_HP;
                }
                else {
                    printMerchantInsufficientCoins(cout);
                    price = NOT_ENOUGH_MONEY;
                }
                break;
            case BUY_BUFF:
                if (player.pay(PRICE_BUFF)) {
                    player.buff(MERCHANT_BUFF);
                    price = PRICE_BUFF;
                }
                else {
                    printMerchantInsufficientCoins(cout);
                    price = NOT_ENOUGH_MONEY;
                }
                break;
        }
        printMerchantSummary(cout, player.getName(), numChoice, price);
    }
}


void Merchant::print(ostream &os) const
{
    printCardDetails(os, m_name);
    printEndOfCardDetails(os);
}


bool checkNumber(string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
