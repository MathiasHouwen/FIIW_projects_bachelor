//
// Created by robin on 16/11/2024.
//

#include "PlayersView.h"

PlayersView::PlayersView(QWidget *parent)
    : QWidget(parent){
}

PlayersView::~PlayersView() = default;

void PlayersView::setPlayers(const std::vector<Player>& players) {
    this->players = players;
}

std::vector<Player> PlayersView::getPlayers() {
    return players;
}
