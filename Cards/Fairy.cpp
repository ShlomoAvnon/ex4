//
// Created by teich on 09/06/2022.
//

#include "Fairy.h"
#include "Wizard.h"

Fairy::Fairy():
        Card(CardType::NoBattle, CardStats(IRRELEVANT, IRRELEVANT, IRRELEVANT, F_HEAL, IRRELEVANT, IRRELEVANT), "Fairy")
{}

void Fairy::applyEncounter(Player &player) const {
    bool result = false;
    const Wizard* isWizard = dynamic_cast<const Wizard*> (&player);
    if(isWizard != nullptr) {
        player.heal(m_stats.heal);
        result = true;
    }
    printFairyMessage(result);
}



void Fairy::print(ostream &os) const
{
    printCardDetails(os, m_name);
    printEndOfCardDetails(os);
}
