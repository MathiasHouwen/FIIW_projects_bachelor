//
// Created by houwe on 8/11/2024.
//

#include <QLabel>
#include <QVBoxLayout>
#include "PieceView.h"

PieceView::PieceView(QWidget *parent)
        : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *imageLabel = new QLabel(this);

    // Load the image into a QPixmap
    QPixmap pixmap("Chaturaji/assets/Chess_prg45.svg"); // Replace with your image file path

    // Set the pixmap to the QLabel
    imageLabel->setPixmap(pixmap);

    // Center the image in the layout
    imageLabel->setAlignment(Qt::AlignCenter);

    // Add QLabel to the layout
    layout->addWidget(imageLabel);

    this->setLayout(layout);
    this->setWindowTitle("Image Display Example");
    this->resize(100, 100);
}