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

Player::Player(Color color, QString name, HomeBoardSide homeBoardSide, int startingScore)
    : color(color), name(name), score(startingScore), homeBoardSide(homeBoardSide) {}

int Player::isBot() const {
    return bot;
}

HomeBoardSide Player::getHomeBoardSide() const {
    return homeBoardSide;
}

