// volledig door mathias

#include "Player.h"

Player::Player(colour mColour) :
    m_colour(mColour),
    m_name("new player"),
    m_alive(true),
    m_score(0) {}


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

Player::colour Player::getColour() const {
    return m_colour;
}

bool Player::operator==(const Player &rhs) const {
    return m_colour == rhs.m_colour; // enkel kleur is in 1 game al genoeg. Zo kan je ook nog players vergelijken voor en na hun naam geinitialisaeerd is
}

bool Player::operator!=(const Player &rhs) const {
    return m_colour != rhs.m_colour; // zie ==
}

void Player::setName(const QString &mName) {
    m_name = mName;
}

QString Player::getColourName(Player::colour colour) {
    switch (colour) {
        case Player::colour::RED: return "red";
        case Player::colour::BLUE: return "blue";
        case Player::colour::GREEN: return "green";
        case Player::colour::YELLOW: return "yellow";
        default: return "Unknow";
    }
}

Player::colour Player::getColourFromName(const QString& colourstr){
    if (colourstr == "red") return Player::colour::RED;
    if (colourstr == "blue") return Player::colour::BLUE;
    if (colourstr == "green") return Player::colour::GREEN;
    if (colourstr == "yellow") return Player::colour::YELLOW;
}

QColor Player::getQColour() {
    switch (m_colour) {
        case Player::colour::RED: return QColor("red");
        case Player::colour::BLUE: return QColor("blue");
        case Player::colour::GREEN: return QColor("green");
        case Player::colour::YELLOW: return QColor("yellow");
        default: return QColor("unknown");
    }
}