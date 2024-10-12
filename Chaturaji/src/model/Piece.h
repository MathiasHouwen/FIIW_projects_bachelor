//
// Created by ebbew on 9-10-2024.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include <QPoint>
#include "Player.h"
#include "Pattern.h"

class Piece {
public:
    enum class Type {PAWN, BOAT, ELEPH, KNIGHT, KING, USED};
    QPoint direction;
    const Pattern &getWalkPattern() const;
    const Pattern &getAttackPattern() const;
    Type getType() const;
    Piece(Type type, QPoint direction, Player& player);
    int getScoreValue() const;
    Type getTypeFromDobbel(int number);
    Player &getPlayer() const;
    static std::string getTypeName(Type type);

private:
    void init(Pattern pattern, int ScoreValue);
    Pattern walkPattern;
    Pattern attackPattern;
    Type type;
    int scoreValue;
    Player& player;
};


#endif //CHATURAJI_PIECE_H
