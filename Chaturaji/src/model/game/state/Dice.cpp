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

bool Dice::allowsType(PieceType type) {
    return getAllowedTypes().contains(type);
}

int Dice::asNumber(int die) {
    return dice[die].number + 1;
}

QSet<PieceType> Dice::getAllowedTypes() {
    QSet<PieceType> set{};
    for(auto die : dice){
        if(die.used) continue;
        set.unite(numberToTypes(die.number));
    }
    return set;
}

bool Dice::isUsed(int die) {
    return dice[die].used;
}

void Dice::setUsed(PieceType type) {
    for(auto& die : dice){
        if(die.used) continue;
        if(numberToTypes(die.number).contains(type)){
            die.used = true;
            break;
        }
    }
}

QSet<PieceType> Dice::numberToTypes(int number) {
    QSet<PieceType> typesMap[6] = {
            {PieceType::PAWN, PieceType::KING},
            {PieceType::BOAT},
            {PieceType::HORSE},
            {PieceType::ELEPHANT},
            {PieceType::PAWN, PieceType::KING},
            {PieceType::ELEPHANT}
    };
    return typesMap[number];
}
