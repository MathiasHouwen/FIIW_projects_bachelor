//
// Created by houwe on 10/11/2024.
//
//volledig van mathias, kleine refactors door ebbe


#ifndef CHATURAJI_PLAYERVIEW_H
#define CHATURAJI_PLAYERVIEW_H


#include <QWidget>
#include <qobjectdefs.h>
#include <qtmetamacros.h>
#include <QLabel>
#include <QColor>
#include <qpen.h>
#include <QPainter>
#include <qpainterpath.h>
#include <QVBoxLayout>
#include "../../../model/game/state/identities/Player.h"

class PlayerView : public QWidget {
Q_OBJECT

public:
    QString ColorToString(Color color);
    PlayerView(Player* player, QWidget *parent);
    void updateScore(int score);
    void updateSetGrey();
    void updateSetBigOrSmall(bool big);

private:
    QColor color;
    QLabel* scoreLabel;
    QLabel* nameLabel;

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CHATURAJI_PLAYERVIEW_H
