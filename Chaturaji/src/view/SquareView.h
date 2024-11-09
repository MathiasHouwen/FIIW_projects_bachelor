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
#include "../model/Game.h"


class SquareView : public QWidget{
Q_OBJECT
private:
    QPoint cell;
    QColor border{Qt::transparent};
    QColor color;
    Game& model;
    PieceWidgit* pieceView{nullptr};
    void getHighLight();
public:
    explicit SquareView(QWidget *parent, QPoint cell, Game& model);
    ~SquareView() override;
protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};



#endif //SQUAREVIEW_H
