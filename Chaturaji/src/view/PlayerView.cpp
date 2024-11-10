//
// Created by houwe on 10/11/2024.
//

#include <qpen.h>
#include <QPainter>
#include <QLabel>

#include "PlayerView.h"


PlayerView::PlayerView(QWidget *parent, Player *player)
        : QWidget(parent), player(player){
}

void PlayerView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

//    QRect boundingBox((width() - width()) / 2, (height() - height()) / 2, width(), height());
    QRect boundingBox(0, 0, width(), height());
    colour = player->getQColour();
    painter.fillRect(boundingBox, colour);

    // Tekst setup
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // Teken tekst
    int padding = 10;
    painter.drawText(padding, 30, "Name: " + player->getName());
    painter.drawText(padding, 60, "Score: " + QString::number(player->getScore()));

    painter.setPen(Qt::black);
    painter.drawRect(boundingBox);
}