//
// Created by teich on 20/06/2022.
//

#include "Card.h"
#include "Queue.h"
#include <memory>

#ifndef MTMCHKIN_CPP_GANG_H
#define MTMCHKIN_CPP_GANG_H

class Gang : public Card{
public:
    Gang(Queue<std::shared_ptr<Card>> queue);
    ~Gang() override =default;

    void applyEncounter(Player& player) const override;


private:
    Queue<std::shared_ptr<Card>> m_gangQueue;

};


#endif //MTMCHKIN_CPP_GANG_H
