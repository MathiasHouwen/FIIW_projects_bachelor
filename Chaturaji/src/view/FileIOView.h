//
// Created by houwe on 11/11/2024.
//

#ifndef CHATURAJI_FILEIOVIEW_H
#define CHATURAJI_FILEIOVIEW_H


#include <QWidget>
#include <QPushButton>
#include "../controller/FileIO.h"

class FileIOView : public QWidget {
Q_OBJECT

public:
    explicit FileIOView(QWidget *parent = nullptr);

private slots:
    void onLoadButtonClicked();
    void onSaveButtonClicked();

private:
    QHBoxLayout *toolbar;
    QPushButton *loadButton;
    QPushButton *saveButton;
};



#endif //CHATURAJI_FILEIOVIEW_H
