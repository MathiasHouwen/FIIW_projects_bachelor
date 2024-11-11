//
// Created by houwe on 11/11/2024.
//

#include <QVBoxLayout>
#include "FileIOView.h"

FileIOView::FileIOView(QWidget *parent)
    : QWidget(parent){

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
}

void FileIOView::onSaveButtonClicked() {
    qDebug("Save button clicked!");
}