//
// Created by ebbew on 13-11-2024.
//

#include <ctime>
#include "Dice.h"

void Dice::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    dice[0].number = std::rand() % 6 + 1;
    dice[1].number = std::rand() % 6 + 1;
}

Dice::Dice() {
    doubleDobbel();
}

bool Dice::allows(Piece::Type type) {
    for(auto die : dice){
        for(int t = 0; t < 2; t++){
            if(die.used) continue;
            if(typesMap[die.number][t] == type) return true;
        }
    }
    return false;
}
