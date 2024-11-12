//
// Created by houwe on 11/11/2024.
//

#include <QVBoxLayout>
#include <QFileDialog>

#include "FileIOView.h"

FileIOView::FileIOView(Game& game, QWidget *parent)
    : QWidget(parent), game(game){

    toolbar = new QHBoxLayout(parent);
    loadButton = new QPushButton("Load", nullptr);
    saveButton = new QPushButton("Save", nullptr);
    toolbar->addWidget(loadButton);
    toolbar->addWidget(saveButton);
    toolbar->setSpacing(0);

    // Signals
    connect(loadButton, &QPushButton::clicked, this, &FileIOView::onLoadButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &FileIOView::onSaveButtonClicked);
}

void FileIOView::onLoadButtonClicked() {
    qDebug("Load button clicked!");
    QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select a file to load",
            "../Saves",
            "Text Files (*.txt)"
    );

    if (!filePath.isEmpty()) {
        qDebug() << "FilePath:" << filePath;
        io.loadBoard(&game, filePath); //TODO: ALS GE LAAD LAAT HAALT HET NIKS WEG
    } else {
        qDebug() << ">:( Geen geldig filepath";
    }
}

void FileIOView::onSaveButtonClicked() {
    qDebug("Save button clicked!");
    QString filePath = QFileDialog::getSaveFileName(
            this,
            "Save File",
            "../Saves",
            "Text Files (*.txt)"
    );

    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
            filePath += ".txt";
        }
        qDebug() << "Saving to file:" << filePath;

        io.saveBoard(&game.getBoard(), filePath);
    } else {
        qDebug() << ">:( Geen naam";
    }
}