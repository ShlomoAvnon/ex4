//
// Created by teich on 20/06/2022.
//

#include "Gang.h"

Gang::Gang(Queue<std::shared_ptr<Card>> queue):
        Card(CardType::Battle, CardStats(IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT), "Gang"),
        m_gangQueue(queue)
{}

void Gang::applyEncounter(Player &player) const {
    Card::applyEncounter(player);
}
