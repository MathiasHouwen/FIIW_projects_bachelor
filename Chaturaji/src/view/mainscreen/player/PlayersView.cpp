#include "PlayersView.h"
#include <QVBoxLayout>
//volledig van robin, kleine refactors door ebbe


PlayersView::PlayersView(QWidget *parent)
    : QWidget(parent) {
    layout = new QVBoxLayout(parent);
    layout->setDirection(QBoxLayout::BottomToTop);
}

void PlayersView::addPlayerView(const Player &player) {
    auto playerView = new PlayerView(player, nullptr);
    players[player.getColour()] = playerView;
    layout->addWidget(playerView);
}

void PlayersView::updateScore(Player::colour color, int score) {
    players[color]->updateScore(score);
}

void PlayersView::updateSetBigAndToTop(Player::colour color) {
    if(bigPlayer){
        bigPlayer->updateSetBigOrSmall(false);
    }
    bigPlayer = players[color];
    bigPlayer->updateSetBigOrSmall(true);
    // remove en add om naar top te brengen
    layout->removeWidget(bigPlayer);
    layout->addWidget(bigPlayer);
}

void PlayersView::updateSetGrey(Player::colour color) {
    players[color]->updateSetGrey();
}

void PlayersView::clear() {
    for(auto playerView : players){
        layout->removeWidget(playerView);
        delete playerView;
    }
    players.clear();
    bigPlayer = nullptr;
}

PlayersView::~PlayersView() = default;
