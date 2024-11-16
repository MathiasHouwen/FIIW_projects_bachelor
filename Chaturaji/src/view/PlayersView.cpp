//
// Created by robin on 16/11/2024.
//

#include "PlayersView.h"

PlayersView::PlayersView(QWidget *parent)
    : QWidget(parent){
}

PlayersView::~PlayersView() = default;

void PlayersView::setPlayers(const QMap<QColor, PlayerView*>& players) {
    this->players = players;
}

QMap<QColor, PlayerView*> PlayersView::getPlayers() {
    return players;
}

void PlayersView::makeLayout() {

}
