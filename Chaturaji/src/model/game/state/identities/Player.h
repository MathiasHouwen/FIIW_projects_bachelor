//
// Created by houwe on 10/10/2024.
//
// veranderingen in practicum 2:
// - player houdt set van pieces bij -> nodig om alle pieces te updaten als die grijs moeten worden

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <QString>
#include "../../enums_and_structs/Color.h"

class Player {
private:
    int score{0};    // huidige score
    bool alive{true};   // leeft nog
    QString name; // naam van wie deze player speelt
    Color color{Color::NONE};
public:
    Player(Color color, QString name, int startingScore); // starting score zodat json reader die kan invullen
    Player() = default;
    void increaseScore(int extraScore);
    void kill();
    [[nodiscard]] int getScore() const;
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] const QString &getName() const;
    [[nodiscard]] Color getColor() const;

};


#endif //CHATURAJI_PLAYER_H
