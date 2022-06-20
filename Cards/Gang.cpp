//
// Created by teich on 20/06/2022.
//

#include "Gang.h"

Gang::Gang(Queue<std::shared_ptr<Card>> queue):
    Card(CardType::Battle, CardStats(IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT), "Gang"),
    m_gangQueue(queue)
{}

void Gang::applyEncounter(Player &player) const {
    Queue<std::shared_ptr<Card>> tempGangQueue = m_gangQueue;
    bool loss = false;

    for (int i = 0; i < m_gangQueue.size(); ++i) {
        if (player.getAttackStrength() >= tempGangQueue.front()->getForce() && !loss) {
            player.addCoins(tempGangQueue.front()->getLoot());
        }
        else {
            player.damage(tempGangQueue.front()->getHPLossOnDefeat());
            player.buff(tempGangQueue.front()->getBuff());
            printLossBattle(player.getName(), tempGangQueue.front()->getName());
            loss = true;
        }
        tempGangQueue.popFront();
    }
    if (!loss){
        player.levelUp();
        printWinBattle(player.getName() ,this->m_name);
    }
}