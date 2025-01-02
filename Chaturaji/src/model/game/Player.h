//
// Created by houwe on 10/10/2024.
//
// veranderingen in practicum 2:
// - player houdt set van pieces bij -> nodig om alle pieces te updaten als die grijs moeten worden

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <iostream>
#include <qstring.h>
#include <qcolor.h>
#include <QSet>
#include "board/Piece.h"
class Piece; // forward decl om circular dependency te voorkomen
class Player {
public:
    enum class colour {RED, BLUE, YELLOW, GREEN};
    Player(colour mColour);
    virtual ~Player() = default;

    //setters
    void setName(const QString &mName);
    void addScore(int score);
    void killPlayer();
    void setMScore(int mScore);
    void addPiece(Piece* piece);
    void removePiece(Piece* piece);

    //getters
    int getScore() const;
    bool isAlive() const;
    const QString &getName() const;
    colour getColour() const;

    static QString getColourName(Player::colour colour);        // vertaalt kleur naar een string woord
    static colour getColourFromName(const QString &colourstr);  // vertaalt terug naar kleur

    // vergelijkers
    bool operator==(const Player &rhs) const;
    bool operator!=(const Player &rhs) const;

    const QSet<Piece *> &getAlivePieces() const;

private:
    int m_score;    // huidige score
    bool m_alive;   // leeft nog
    QString m_name; // naam van wie deze player speelt
    colour m_colour;
    QSet<Piece*> pieces{};
};


#endif //CHATURAJI_PLAYER_H
