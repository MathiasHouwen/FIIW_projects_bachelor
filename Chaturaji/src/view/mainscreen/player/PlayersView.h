//
// Created by robin on 16/11/2024.
//

#ifndef PLAYERSVIEW_H
#define PLAYERSVIEW_H
#include <QVBoxLayout>
#include <QWidget>
#include "PlayerView.h"


class PlayersView: public QWidget{
Q_OBJECT
public:
    explicit PlayersView(QWidget *parent = nullptr);
    ~PlayersView() override;
    void addPlayerView(const Player& player);

    void updateScore(Player::colour color, int score);
    void updateSetBigAndToTop(Player::colour color);
    void updateSetGrey(Player::colour color);
    void clear();

private:
    QMap<Player::colour, PlayerView*> players;
    PlayerView* bigPlayer{nullptr};
    QVBoxLayout* layout;
};



#endif //PLAYERSVIEW_H
