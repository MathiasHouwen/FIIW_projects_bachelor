//
// Created by ebbew on 8-11-2024.
//

#ifndef CHATURAJI_BOARDVIEW_H
#define CHATURAJI_BOARDVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include "../model/Board.h"
#include "../model/Game.h"
#include "SquareView.h"

class BoardView : public QWidget{
Q_OBJECT

private:
    QVBoxLayout *layoutRows;
    SquareView* squareViews[Board::getSize()][Board::getSize()];
public:
    explicit BoardView(QWidget* widget);
    void updateHighlight(QPoint cell, SquareView::HighLight highlight);
    void updateHighlights(const QList<QPoint>& cells, SquareView::HighLight highlight);
    void updatePiece(QPoint cell, Piece* piece);
    ~BoardView() override;

signals:
    void cellClicked(QPoint cell);

private slots:
    void onSquareViewClicked(QPoint cell);
    //QVBoxLayout* rows;
    //Game& model;
    //explicit BoardView(Game& model, QWidget *parent = nullptr);


};




#endif //CHATURAJI_BOARDVIEW_H
