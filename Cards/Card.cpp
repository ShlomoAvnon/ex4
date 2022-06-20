//
// Created by teich on 04/05/2022.
//
#include "Card.h"
#include <iostream>


Card::Card(CardType type, const CardStats stats, std::string name):
    m_name(name),
    m_effect(type),
    m_stats(stats)
{}


ostream &operator<<(ostream &os, const Card &card) {
    card.print(os);
    return os;
}

void Card::print(ostream &os) const {}

void Card::applyEncounter(Player &player) const {}

int Card::getForce() {
    return m_stats.force;
}

int Card::getBuff() {
    return m_stats.buff;
}

int Card::getHPLossOnDefeat() {
    return m_stats.hpLossOnDefeat;
}

int Card::getLoot() {
    return m_stats.loot;
}

string Card::getName() {
    return m_name;
}
