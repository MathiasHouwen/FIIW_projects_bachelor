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
    void setPlayers(const QMap<QString, PlayerView*>& players);
    QMap<QString, PlayerView*> getPlayers();

PlayerView *getPlayerFromColor(QColor color);
    void addPlayerFromColor(PlayerView *playerview, QColor color);
private:
    QMap<QString, PlayerView*> players;
protected:
    void paintEvent(QPaintEvent *event) override;
};



#endif //PLAYERSVIEW_H
