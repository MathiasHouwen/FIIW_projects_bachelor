//
// Created by houwe on 10/11/2024.
//

#include <qpen.h>
#include <QPainter>
#include <QLabel>
#include <qpainterpath.h>

#include "PlayerView.h"


PlayerView::PlayerView(QWidget *parent, Player *player, Game* game)
        : QWidget(parent), player(player), game(game){
    setMinimumSize(250, 80);
}

void PlayerView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QPainterPath path;
    QPen strokePen;

    if (*player == game->getCurrentPlayer()) { // Use the Player method to check turn
        setMinimumSize(250, 250); // Larger size for the current player
    } else {
        setMinimumSize(250, 70); // Default size for others
    }

    //    QRect boundingBox((width() - width()) / 2, (height() - height()) / 2, width(), height());
    QRect boundingBox(0, 0, width(), height());
    colour = player->getQColour();
    path.addRoundedRect(boundingBox, 15, 15);  // Rounded corners with radius 15
    painter.fillPath(path, QColorConstants::Svg::grey);

    // Tekst setup
    QFont font = painter.font();
    font.setPointSize(14);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // Teken tekst
    int padding = 10;
    painter.drawText(padding, 30, "Name: " + player->getName());
    painter.drawText(padding, 60, "Score: " + QString::number(player->getScore()));

    strokePen.setColor(colour);
    strokePen.setWidth(10);
    strokePen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(strokePen);

    painter.drawPath(path);
}