//
// Created by ebbew on 13-11-2024.
//

#include <ctime>
#include "Dice.h"

void Dice::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for(auto& die : dice){
        die.number = std::rand() % 6;
        die.used = false;
    }
}

Dice::Dice() {
    doubleDobbel();
}

bool Dice::allows(Piece::Type type) {
    return getAllowedTypes().contains(type);
}

int Dice::getNumber(int die) {
    return dice[die].number + 1;
}

QSet<Piece::Type> Dice::getAllowedTypes() {
    QSet<Piece::Type> set{};
    for(auto die : dice){
        for(int t = 0; t < 2; t++){
            if(die.used) continue;
            set.insert(typesMap[die.number][t]);
        }
    }
    return set;
}

bool Dice::isUsed(int die) {
    return dice[die].used;
}

void Dice::setUsed(Piece::Type type) {
    for(auto& die : dice){
        bool used = false;
        for(int t = 0; t < 2; t++){
            if(typesMap[die.number][t] != type) continue;
            die.used = true;
            used = true;
        }
        if(used) break;
    }
}
