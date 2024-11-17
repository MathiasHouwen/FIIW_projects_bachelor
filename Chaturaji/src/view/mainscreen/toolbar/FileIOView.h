//
// Created by houwe on 11/11/2024.
//
//volledig van mathias

#ifndef CHATURAJI_FILEIOVIEW_H
#define CHATURAJI_FILEIOVIEW_H


#include <QWidget>
#include <QPushButton>
#include "../../../model/io/FileIO.h"

class FileIOView : public QWidget {
Q_OBJECT

public:
    explicit FileIOView(Game& game, QWidget *parent = nullptr);

signals:
    void onLoad();
    void onSave();

private slots:
    void onLoadButtonClicked();
    void onSaveButtonClicked();

private:
    Game& game;
    FileIO io;

    QHBoxLayout *toolbar;
    QPushButton *loadButton;
    QPushButton *saveButton;
};



#endif //CHATURAJI_FILEIOVIEW_H
