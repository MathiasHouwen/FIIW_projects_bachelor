//
// Created by houwe on 10/11/2024.
//

#ifndef CHATURAJI_PLAYERVIEW_H
#define CHATURAJI_PLAYERVIEW_H


#include <QWidget>
#include "../model/Player.h"

class PlayerView : public QWidget {
Q_OBJECT

public:
    PlayerView(QWidget *parent, Player* player);

private:
    Player* player;
    QColor colour;

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CHATURAJI_PLAYERVIEW_H
