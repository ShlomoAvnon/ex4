//
// Created by shlom on 09/06/2022.
//
#include "Mtmchkin.h"
int main(){
    try {
        Mtmchkin game("deck.txt");
        while (!game.isGameOver()) {
            game.playRound();
            game.printLeaderBoard();
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
    return 0;
}
