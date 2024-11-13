//
// Created by houwe on 10/10/2024.
//

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <iostream>
#include <qstring.h>
#include <qcolor.h>

class Player {
public:
    enum class colour {RED, BLUE, YELLOW, GREEN};
    Player(colour mColour);

    //setters
    void setName(const QString &mName);
    void addScore(int score);
    void killPlayer();
    void setMScore(int mScore);

    //getters
    int getScore() const;
    bool isAlive() const;
    const QString &getName() const;
    colour getColour() const;

    static QString getColourName(Player::colour colour);        // vertaalt kleur naar een string woord
    QColor getQColour();                                        // geeft colour in QColour format
    static colour getColourFromName(const QString &colourstr);  // vertaalt terug naar kleur

    // vergelijkers
    bool operator==(const Player &rhs) const;
    bool operator!=(const Player &rhs) const;

private:
    int m_score;    // huidige score
    bool m_alive;   // leeft nog
    QString m_name; // naam van wie deze player speelt
    colour m_colour;

};


#endif //CHATURAJI_PLAYER_H
