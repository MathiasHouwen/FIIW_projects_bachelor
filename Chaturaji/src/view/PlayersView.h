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
    explicit PlayersView(QWidget *parent = 0);
    ~PlayersView() override;
    void setPlayers(const QMap<Player::colour, PlayerView*>& players);
    QMap<Player::colour, PlayerView*> getPlayers();
    void updatePlayers();
    PlayerView *getPlayerFromColor(Player::colour color);
    void addPlayerFromColor(PlayerView *playerview, Player::colour color);
private:
    QMap<Player::colour, PlayerView*> players;
    QVBoxLayout *layout;
};



#endif //PLAYERSVIEW_H
