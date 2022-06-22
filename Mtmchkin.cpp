//
// Created by teich on 09/06/2022.
//
#include "Players/Player.h"
#include "Cards/Card.h"
#include "Mtmchkin.h"
#include "Cards/Vampire.h"
#include "Cards/Barfight.h"
#include "Cards/Dragon.h"
#include "Cards/Fairy.h"
#include "Cards/Goblin.h"
#include "Cards/Merchant.h"
#include "Cards/Pitfall.h"
#include "Cards/Treasure.h"
#include "Cards/Gang.h"
#include "Players/Rogue.h"
#include "Players/Wizard.h"
#include "Players/Fighter.h"
#include "Exception.h"
#include <fstream>
#include <memory>
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
const int NUM_OF_CARDS = 9;
const int GOBLIN = 0;
const int VAMPIRE = 1;
const int DRAGON = 2;
const int MERCHANT = 3;
const int TREASURE = 4;
const int PITFALL = 5;
const int BARFIGHT = 6;
const int FAIRY = 7;
const int GANG = 8;
const int ROGUE = 0;
const int WIZARD = 1;
const int MAX_CHARACTER = 15;
const int NUM_OF_PLAYERS = 3;
const int NUM_OF_MONSTERS = 3;
const char SPACE = ' ';
const char LINEBREAK = '\n';
const string ABC = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string CARDS_STR[9] = {"Goblin", "Vampire", "Dragon", "Merchant", "Treasure", "Pitfall", "Barfight", "Fairy", "Gang"};
const string PLAYERS_STR[3] = {"Rogue", "Wizard", "Fighter"};
const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 6;
const int MIN_CARDS = 5;
const int NON_LOSERS_QUEUES = 2;

std::shared_ptr<Card> intToCard(int i, Queue<std::shared_ptr<Card>> queue);
bool checkNumber(string str);
void printBack(Queue<std::shared_ptr<Player>> queue, int& i);
bool isValidName(const string name);
std::shared_ptr<Player> intToPlayer(int i, string name, string type);

Mtmchkin::Mtmchkin(const std::string fileName):
        m_roundCount(1),
        m_numOfPlayers(0) {
    printStartGameMessage();

    ifstream source(fileName);
    string cardType;
    if (!source) {
        throw DeckFileNotFound();
    }
    if (source.peek() == std::ifstream::traits_type::eof()) {
        throw DeckFileInvalidSize();
    }
    int lineOfException = 0;
    string strLineOfException;
    Queue<std::shared_ptr<Card>> gangQueue;

    while (getline(source, cardType)) {
        lineOfException++;
        strLineOfException = std::to_string(lineOfException);
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            if (!CARDS_STR[i].compare(cardType)) {
                if (i == GANG) {

                    while (getline(source, cardType) && cardType.compare("EndGang")) {
                        lineOfException++;
                        strLineOfException = std::to_string(lineOfException);
                        for (int k = 0; k < NUM_OF_MONSTERS; ++k) {
                            if (!CARDS_STR[k].compare(cardType)) {
                                gangQueue.pushBack(intToCard(k, gangQueue));
                                break;
                            } else if (k == NUM_OF_MONSTERS - 1) {
                                throw DeckFileFormatError(strLineOfException);
                            }
                        }
                    }
                    if (cardType != "EndGang") {
                        throw DeckFileFormatError(strLineOfException);
                    }
                }
                m_cardsQueue.pushBack(intToCard(i, gangQueue));
                break;
            } else if (i == NUM_OF_CARDS - 1) {
                throw DeckFileFormatError(strLineOfException);
            }
        }
    }
    source.close();
    if (m_cardsQueue.size() < MIN_CARDS) {
        throw DeckFileInvalidSize();
    }

    //gets the team size

    string str_numOfPlayers;
    bool isValid= false;
    do {
        printEnterTeamSizeMessage();
        getline(cin, str_numOfPlayers, LINEBREAK);
        isValid = checkNumber(str_numOfPlayers);
        if (isValid && str_numOfPlayers.length()){
            m_numOfPlayers = std::stoi(str_numOfPlayers);
        }
        if (m_numOfPlayers < MIN_PLAYERS || m_numOfPlayers > MAX_PLAYERS) {
            printInvalidTeamSize();
        }
    } while (m_numOfPlayers < MIN_PLAYERS || m_numOfPlayers > MAX_PLAYERS || !isValid);

    //check the validity of the name and the roll
    string name;
    string type;
    bool isValidPlayer = true;
    for (int i = 0; i < m_numOfPlayers; ++i) {
        if(isValidPlayer) {
            printInsertPlayerMessage();
        }
        {
            getline(cin, name, SPACE);
            getline(cin, type, LINEBREAK);
            if (!isValidName(name)) {
                i--;
                printInvalidName();
                isValidPlayer = false;
            } else {
                for (int p = 0; p < NUM_OF_PLAYERS; ++p) {
                    if (!(PLAYERS_STR[p].compare(type))) {
                        m_playersQueue.pushBack((intToPlayer(p, name, type)));
                        isValidPlayer = true;
                        break;
                    }
                    else if (p == NUM_OF_PLAYERS-1) {
                        i--;
                        isValidPlayer = false;
                        printInvalidClass();
                    }
                }
            }
        }
    }
}


std::shared_ptr<Player> intToPlayer(int i, string name, string type)
{
    switch (i) {
        case (ROGUE): {
            std::shared_ptr<Rogue> rogue (new Rogue(name, type));
            return rogue;
        }
        case (WIZARD): {
            std::shared_ptr<Wizard> wizard(new Wizard(name, type));
            return wizard;
        }
    }
    std::shared_ptr<Fighter> fighter (new Fighter(name, type));
    return fighter;
}

std::shared_ptr<Card> intToCard(int i, Queue<std::shared_ptr<Card>> queue)
{
    switch (i) {
        case (GOBLIN): {
            std::shared_ptr<Goblin> goblin(new Goblin());
            return goblin;
        }
        case (VAMPIRE): {
            std::shared_ptr<Vampire> vampire (new Vampire());
            return vampire;
        }
        case (DRAGON): {
            std::shared_ptr<Dragon> dragon (new Dragon());
            return dragon;
        }
        case (MERCHANT): {
            std::shared_ptr<Merchant> merchant(new Merchant());
            return merchant;
        }
        case (TREASURE): {
            std::shared_ptr<Treasure> treasure (new Treasure());
            return treasure;
        }
        case (PITFALL): {
            std::shared_ptr<Pitfall> pitfall (new Pitfall());
            return pitfall;
        }
        case (BARFIGHT): {
            std::shared_ptr<Barfight> barfight (new Barfight());
            return barfight;
        }
        case (FAIRY):{
            std::shared_ptr<Fairy> fairy(new Fairy());
            return fairy;
        }
    }
    std::shared_ptr<Gang> gang(new Gang(queue));
    return gang;
}


void Mtmchkin::playRound()
{
    if(!isGameOver()) {
        int activePlayers = m_playersQueue.size();
        printRoundStartMessage(m_roundCount);
        for (int j = 0; j < activePlayers; j++) {
            printTurnStartMessage(m_playersQueue.front()->getName());
            std::shared_ptr<Card> currentCard = m_cardsQueue.front();
            currentCard->applyEncounter(*m_playersQueue.front());
            m_cardsQueue.popFront();
            m_cardsQueue.pushBack(currentCard);

            // checking if player win
            if (m_playersQueue.front()->getLevel() == MAX_LEVEL) {
                m_winnersPlayers.pushBack(m_playersQueue.front());
                m_playersQueue.popFront();
            }
                // checking if player lost
            else if (m_playersQueue.front()->isKnockedOut()) {
                m_losersPlayers.pushBack(m_playersQueue.front());
                m_playersQueue.popFront();
            }
                // else - the player continue to play
            else {
                m_playersQueue.pushBack(m_playersQueue.front());
                m_playersQueue.popFront();
            }
            // checking if game over
            if (isGameOver())
                printGameEndMessage();
        }
        m_roundCount++;
    }
}

int Mtmchkin::getNumberOfRounds() const {
    return m_roundCount-1;
}

bool Mtmchkin::isGameOver() const {
    return (m_winnersPlayers.size()+ m_losersPlayers.size()==m_numOfPlayers);
}


void Mtmchkin::printLeaderBoard() const {
    printLeaderBoardStartMessage();
    int i=1;
    Queue<std::shared_ptr<Player>> tmpQueue = m_winnersPlayers;
    for(int j = 0; j<NON_LOSERS_QUEUES; j++){
        while(!tmpQueue.isEmpty()){
            printPlayerLeaderBoard(i, *tmpQueue.front());
            tmpQueue.popFront();
            i++;
        }
        tmpQueue = m_playersQueue;
    }
    tmpQueue = m_losersPlayers;
    printBack(tmpQueue, i);

}

void printBack(Queue<std::shared_ptr<Player>> queue, int& i)
{
    if(queue.isEmpty())
        return;
    std::shared_ptr<Player> player = queue.front();
    queue.popFront();
    printBack(queue, i);
    printPlayerLeaderBoard(i, *player);
    i++;
}

bool isValidName(const string name)
{
    if(name.length() >= MAX_CHARACTER){
        return false;
    }
    return name.find_first_not_of(ABC) == std::string::npos;
}