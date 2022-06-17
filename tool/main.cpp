//
// Created by shlom on 09/06/2022.
//
#include "Mtmchkin.h"
int main(){
const int MAX_NUMBER_OF_ROUNDS = 100;
    Mtmchkin game("deck.txt");
    while(!game.isGameOver() && game.getNumberOfRounds() < MAX_NUMBER_OF_ROUNDS) {
            game.playRound();
        }
    game.printLeaderBoard();
}
