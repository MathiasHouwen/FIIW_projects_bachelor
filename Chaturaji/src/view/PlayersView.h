//
// Created by robin on 16/11/2024.
//

#ifndef PLAYERSVIEW_H
#define PLAYERSVIEW_H
#include <QWidget>
#include "../model/Player.h"


class PlayersView: public QWidget{
Q_OBJECT
public:
    explicit PlayersView(QWidget *parent = 0);
    ~PlayersView() override;
    void setPlayers(const std::vector<Player>& players);
    std::vector<Player> getPlayers();
private:
    std::vector<Player> players;
};



#endif //PLAYERSVIEW_H
