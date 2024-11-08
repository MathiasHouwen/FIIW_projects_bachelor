//
// Created by houwe on 8/11/2024.
//

#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QCoreApplication>
#include <iostream>
#include "PieceWidgit.h"

PieceWidgit::PieceWidgit(QWidget *parent)
        : QWidget(parent) {
    QLabel *imageLabel = new QLabel(this);

    std::cout << ASSET_PATH << std::endl;
    QPixmap pixmap(QString(ASSET_PATH) + "/Chess_prg45.svg"); // Replace with your image file path

    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
}