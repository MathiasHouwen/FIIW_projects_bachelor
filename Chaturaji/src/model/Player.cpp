//
// Created by houwe on 10/10/2024.
//

#include "Player.h"

Player::Player(const std::string &mNaam) : m_name(mNaam) {
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

const std::string &Player::getName() const {
    return m_name;
}
