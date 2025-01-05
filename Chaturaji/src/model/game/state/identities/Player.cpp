// volledig door mathias

#include "Player.h"


void Player::increaseScore(int extraScore) {
    score += extraScore;
}

void Player::kill() {
    alive = false;
}

int Player::getScore() const {
    return score;
}

bool Player::isAlive() const {
    return alive;
}

const QString &Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}

Player::Player(Color color, QString name, int startingScore)
    : color(color), name(name), score(startingScore) {}

int Player::getIsBot() const {
    return isBot;
}

