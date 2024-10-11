//
// Created by houwe on 10/10/2024.
//

#ifndef CHATURAJI_PLAYER_H
#define CHATURAJI_PLAYER_H

#include <iostream>

class Player {
public:
    enum class colour {RED, BLUE, YELLOW, GREEN};
    explicit Player(const std::string &mName, colour mColour);
    void setScore(int score);
    void killPlayer();
    int getScore() const;
    bool isAlive() const;
    const std::string &getName() const;

private:
    int m_score;
    bool m_alive;
    std::string m_name;
    colour m_colour;
};


#endif //CHATURAJI_PLAYER_H
