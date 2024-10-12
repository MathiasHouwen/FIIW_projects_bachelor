//
// Created by houwe on 10/10/2024.
//

#include "Player.h"

Player::Player(colour mColour) :
    m_colour(mColour),
    m_name("new player"),
    m_alive(true),
    m_score(0) {}

void Player::setScore(int score) {
    m_score = score;
}
void Player::addScore(int score) {
    m_score += score;
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

Player::colour Player::getMColour() const {
    return m_colour;
}

bool Player::operator==(const Player &rhs) const {
    return m_colour == rhs.m_colour;
}

bool Player::operator!=(const Player &rhs) const {
    return m_colour != rhs.m_colour;;
}

void Player::setMName(const QString &mName) {
    m_name = mName;
}
