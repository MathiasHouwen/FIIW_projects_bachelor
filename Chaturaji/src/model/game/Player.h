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
#include "board/BadPieceClass.h"
class BadPieceClass; // forward decl om circular dependency te voorkomen
class Player {
public:
    enum class colour {RED, BLUE, YELLOW, GREEN};
    Player(colour mColour);

    //setters
    virtual void setName(const QString &mName);
    virtual void addScore(int score);
    virtual void killPlayer();
    virtual void setMScore(int mScore);
    virtual void addPiece(BadPieceClass* piece);
    virtual void removePiece(BadPieceClass* piece);

    //getters
    virtual int getScore() const;
    virtual bool isAlive() const;
    virtual const QString &getName() const;
    virtual colour getColour() const;

    static QString getColourName(Player::colour colour);        // vertaalt kleur naar een string woord
    static colour getColourFromName(const QString &colourstr);  // vertaalt terug naar kleur

    // vergelijkers
    virtual bool operator==(const Player &rhs) const;
    virtual bool operator!=(const Player &rhs) const;

    virtual const QSet<BadPieceClass *> &getAlivePieces() const;

private:
    int m_score;    // huidige score
    bool m_alive;   // leeft nog
    QString m_name; // naam van wie deze player speelt
    colour m_colour;
    QSet<BadPieceClass*> pieces{};
};


#endif //CHATURAJI_PLAYER_H
