//
// Created by houwe on 10/10/2024.
//

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <iostream>
#include <qstring.h>

class Player {
public:
    enum class colour {RED, BLUE, YELLOW, GREEN};
    Player(colour mColour);

    void setScore(int score);

    void setMName(const QString &mName);

    void addScore(int score);
    void killPlayer();
    int getScore() const;
    bool isAlive() const;
    const QString &getName() const;

    colour getMColour() const;

    bool operator==(const Player &rhs) const;

    bool operator!=(const Player &rhs) const;

private:
    int m_score;
    bool m_alive;
    QString m_name;
    colour m_colour;
};


#endif //CHATURAJI_PLAYER_H
