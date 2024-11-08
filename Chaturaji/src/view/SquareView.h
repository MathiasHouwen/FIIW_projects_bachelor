//
// Created by robin on 8/11/2024.
//

#ifndef SQUAREVIEW_H
#define SQUAREVIEW_H
#include <qobjectdefs.h>
#include <qtmetamacros.h>
#include <QWidget>
#include <QBoxLayout>
#include <qgraphicsitem.h>

#include "../model/Square.h"


class SquareView : public QWidget{
Q_OBJECT
private:
    const Square &square;
    void drawSquare(int index);
public:
    explicit SquareView(const Square &square, QWidget *parent, int index);
    ~SquareView() override;
};



#endif //SQUAREVIEW_H
