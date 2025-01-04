//
// Created by ebbew on 13-11-2024.
//
//volledig van ebbe, nieuw sinds practicum 2

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

bool Dice::allows(BadPieceClass::Type type) {
    return getAllowedTypes().contains(type);
}

int Dice::getNumber(int die) {
    return dice[die].number + 1;
}

QSet<BadPieceClass::Type> Dice::getAllowedTypes() {
    QSet<BadPieceClass::Type> set{};
    for(auto die : dice){
        if(die.used) continue;
        set.unite(typesMap[die.number]);
    }
    return set;
}

bool Dice::isUsed(int die) {
    return dice[die].used;
}

void Dice::setUsed(BadPieceClass::Type type) {
    for(auto& die : dice){
        if(die.used) continue;
        if(typesMap[die.number].contains(type)){
            die.used = true;
            break;
        }
    }
}
