//
// Created by robin on 16/11/2024.
//

#include "PlayersView.h"

#include <QPainter>
#include <qpainterpath.h>

PlayersView::PlayersView(QWidget *parent)
    : QWidget(parent){
    update();
}

PlayersView::~PlayersView() = default;

void PlayersView::setPlayers(const QMap<QString, PlayerView*>& players) {
    this->players = players;
}

QMap<QString, PlayerView*> PlayersView::getPlayers() {
    return players;
}

PlayerView *PlayersView::getPlayerFromColor(QColor color) {
    QString colorString = color.name();
    return players[colorString];
}

void PlayersView::addPlayerFromColor(PlayerView *playerview, QColor color) {
    QString colorString = color.name();
    players[colorString] = playerview;
}

void PlayersView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect *rect = new QRect(0, 0, 100, 100);
    painter.fillRect(*rect, Qt::white);
//
//    //    QRect boundingBox((width() - width()) / 2, (height() - height()) / 2, width(), height());
//    QRect boundingBox(0, 0, width(), height());
//    colour = player->getQColour();
//    QPainterPath path;
//    path.addRoundedRect(boundingBox, 15, 15);  // Rounded corners with radius 15
//    painter.fillPath(path, colour);
//
//    // Tekst setup
//    QFont font = painter.font();
//    font.setPointSize(14);
//    painter.setFont(font);
//    painter.setPen(Qt::white);
//
//    // Teken tekst
//    int padding = 10;
//    painter.drawText(padding, 30, "Name: " + player->getName());
//    painter.drawText(padding, 60, "Score: " + QString::number(player->getScore()));
//
//    painter.setPen(Qt::black);
//    painter.drawPath(path);
}