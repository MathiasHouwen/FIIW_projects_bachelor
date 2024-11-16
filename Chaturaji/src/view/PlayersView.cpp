#include "PlayersView.h"
#include <QVBoxLayout>

PlayersView::PlayersView(QWidget *parent)
    : QWidget(parent), layout(new QVBoxLayout(this)) {
    setLayout(layout); // Set layout for this widget
}

PlayersView::~PlayersView() = default;

void PlayersView::setPlayers(const QMap<Player::colour, PlayerView*>& players) {
    this->players = players;

    // Clear existing widgets from the layout
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Add new PlayerView widgets to the layout
    for (auto it = players.begin(); it != players.end(); ++it) {
        layout->addWidget(it.value());
    }
}

QMap<Player::colour, PlayerView*> PlayersView::getPlayers() {
    return players;
}

PlayerView* PlayersView::getPlayerFromColor(Player::colour color) {
    return players.value(color, nullptr);
}

void PlayersView::addPlayerFromColor(PlayerView* playerView, Player::colour color) {
    players[color] = playerView;
    layout->addWidget(playerView); // Add to layout
}

void PlayersView::updatePlayers() {
    std::cout << "PlayersView::updatePlayers" << std::endl;
}
