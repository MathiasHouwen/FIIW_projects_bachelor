//
// Created by houwe on 11/11/2024.
//
//volledig van mathias


#include <QVBoxLayout>
#include <QFileDialog>

#include "FileIOView.h"

FileIOView::FileIOView(Game& game, QWidget *parent)
    : game(game){

    parent->layout()->addWidget(this);
    toolbar = new QHBoxLayout(this);
    toolbar->setContentsMargins(0,0,0,0);
    toolbar->setAlignment(Qt::AlignRight);
    loadButton = new QPushButton("Load", nullptr);
    saveButton = new QPushButton("Save", nullptr);
    toolbar->addWidget(loadButton);
    toolbar->addWidget(saveButton);
    toolbar->setSpacing(8);

    // Signals
    connect(loadButton, &QPushButton::clicked, this, &FileIOView::onLoadButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &FileIOView::onSaveButtonClicked);
}

void FileIOView::onLoadButtonClicked() {
    emit onLoad();
}

void FileIOView::onSaveButtonClicked() {
    emit onSave();
}