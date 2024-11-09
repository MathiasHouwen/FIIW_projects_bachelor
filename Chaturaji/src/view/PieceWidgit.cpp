//
// Created by houwe on 8/11/2024.
//

#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QCoreApplication>
#include <QSvgRenderer>
#include <iostream>

#include "PieceWidgit.h"

PieceWidgit::PieceWidgit(QWidget *parent)
        : QWidget(parent) {

    svg = new QSvgWidget(this);

    svg->load(QString(ASSET_PATH) + "/Chess_prg45.svg");


}

void PieceWidgit::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    svg->setFixedSize(width(), height());
}

void PieceWidgit::setHovered(bool hovered) {
    this->hovered = hovered;
    if(hovered) {
        svg->move(svg->x(), svg->y() - 4);
    }else{
        svg->move(svg->x(), svg->y() + 4);
    }
}
