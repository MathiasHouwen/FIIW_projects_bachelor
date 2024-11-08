//
// Created by ebbew on 8-11-2024.
//

#ifndef CHATURAJI_BOARDVIEW_H
#define CHATURAJI_BOARDVIEW_H


#include <QWidget>

class BoardView : public QWidget{
Q_OBJECT

public:
    explicit BoardView(QWidget *parent);

    ~BoardView() override;
};


#endif //CHATURAJI_BOARDVIEW_H
