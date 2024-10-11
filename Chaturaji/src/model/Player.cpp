//
// Created by houwe on 10/10/2024.
//

#include <qstring.h>
#include "Player.h"

Player::Player(const QString &mName, Player::colour mColour) : m_name(mName), m_colour(mColour) {
    m_alive = true;
    m_score = 0;
}

void Player::setScore(int score) {
    m_score = score;
}

void Player::killPlayer() {
    m_alive = false;
}

int Player::getScore() const {
    return m_score;
}

bool Player::isAlive() const {
    return m_alive;
}

const QString &Player::getName() const {
    return m_name;
}

Player::Player() {}
