//
// Created by ebbew on 12-11-2024.
//

#ifndef CHATURAJI_CONTROLLER_H
#define CHATURAJI_CONTROLLER_H

#include <qobject.h>
#include <qobjectdefs.h>
#include "../model/Game.h"
#include "../view/BoardView.h"


class Controller: public QObject{
Q_OBJECT

private:
    Game& model;
    BoardView& boardView;
public:
    Controller(Game &model, BoardView& boardView);

private slots:
    void onCellClicked(QPoint cell);
};


#endif //CHATURAJI_CONTROLLER_H
