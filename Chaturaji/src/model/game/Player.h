//
// Created by houwe on 10/10/2024.
//
// veranderingen in practicum 2:
// - player houdt set van pieces bij -> nodig om alle pieces te updaten als die grijs moeten worden

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <QString>
#include "Color.h"
#include "board/BadPieceClass.h"

class Player {
private:
    int score;    // huidige score
    bool alive;   // leeft nog
    QString name; // naam van wie deze player speelt
    Color color;
public:
    Player(Color color, QString name, int startingScore); // starting score zodat json reader die kan invullen

    void increaseScore(int extraScore);
    void kill();
    [[nodiscard]] int getScore() const;
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] const QString &getName() const;
    [[nodiscard]] Color getColor() const;

};


#endif //CHATURAJI_PLAYER_H
