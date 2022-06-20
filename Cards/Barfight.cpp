//
// Created by teich on 09/06/2022.
//

#include "Barfight.h"
#include "Fighter.h"

Barfight::Barfight():
        Card(CardType::NoBattle, CardStats(IRRELEVANT, BF_HP_LOSS, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT), "Barfight")
{}

void Barfight::applyEncounter(Player &player) const {
    bool isFighter = true;
    const Fighter* notFighter = dynamic_cast<const Fighter*> (&player);
    if(notFighter ==nullptr) {
        player.damage(m_stats.hpLossOnDefeat);
        isFighter = false;
    }
    printBarfightMessage(isFighter);
}


void Barfight::print(ostream &os) const
{
    printCardDetails(os, m_name);
    printEndOfCardDetails(os);
}
