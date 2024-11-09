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
#include <QPainter>
#include <QPushButton>

#include "../model/Square.h"
#include "PieceWidgit.h"


class SquareView : public QWidget{
Q_OBJECT
private:
    int xIndex, yIndex;
    bool border{false};
    QColor color;
    PieceWidgit* piece;
public:
    explicit SquareView(QWidget *parent, int xIndex, int yIndex);
    ~SquareView() override;
protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};



#endif //SQUAREVIEW_H
