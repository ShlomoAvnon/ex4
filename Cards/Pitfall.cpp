//
// Created by shlom on 09/06/2022.
//
#include "Pitfall.h"
#include "Rogue.h"

Pitfall::Pitfall():
        Card(CardType::NoBattle, CardStats(IRRELEVANT, P_HP_LOSS, IRRELEVANT, IRRELEVANT, IRRELEVANT, IRRELEVANT), "Pitfall")
{}

void Pitfall::applyEncounter(Player &player) const {
    bool isRogue = true;
    const Rogue* notRogue = dynamic_cast<const Rogue*> (&player);
    if(notRogue == nullptr) {
        player.damage(m_stats.hpLossOnDefeat);
        isRogue = false;
    }
    printPitfallMessage(isRogue);
}


void Pitfall::print(ostream &os) const
{
    printCardDetails(os, m_name);
    printEndOfCardDetails(os);
}

