//
// Created by robin on 16/11/2024.
//

#ifndef PLAYERSVIEW_H
#define PLAYERSVIEW_H
#include <QWidget>
#include "PlayerView.h"


class PlayersView: public QWidget{
Q_OBJECT
public:
    explicit PlayersView(QWidget *parent = 0);
    ~PlayersView() override;
    void setPlayers(const QMap<QColor, PlayerView*>& players);
    QMap<QColor, PlayerView*> getPlayers();
    PlayerView getPlayerFromColor(QColor);
    void addPlayerFromColor(PlayerView, QColor);
    void makeLayout();
private:
    QMap<QColor, PlayerView*> players;
};



#endif //PLAYERSVIEW_H
