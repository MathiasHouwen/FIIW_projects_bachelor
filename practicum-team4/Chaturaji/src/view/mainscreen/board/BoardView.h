//
// Created by ebbew on 8-11-2024.
//
//begin vooral door mathias gemaakt. door Ebbe goed werkend gemaakt


#ifndef CHATURAJI_BOARDVIEW_H
#define CHATURAJI_BOARDVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include "../../../model/game/state/Board.h"
#include "SquareView.h"

class BoardView : public QWidget{
Q_OBJECT

private:
    QGridLayout *layout;
    QHash<QPoint, SquareView*> squareViews{};
public:
    explicit BoardView(QWidget* widget);
    void updateHighlight(QPoint cell, SquareView::HighLight highlight);
    void updateHighlights(const QSet<QPoint>& cells, SquareView::HighLight highlight);
    void updatePiece(QPoint cell, Piece piece);
    void removePiece(QPoint cell);
    void updateFullBoard(const Board& board);
    void updateSetPieceGrey(QPoint cell);
    ~BoardView() override;

signals:
    void cellClicked(QPoint cell);
    void cellHoverChanged(QPoint cell, bool hover);

private slots:
    void onSquareViewClicked(QPoint cell);
    void onSquareHoverUpdated(QPoint cell, bool hover);

    //QVBoxLayout* rows;
    //Game& model;
    //explicit BoardView(Game& model, QWidget *parent = nullptr);


};




#endif //CHATURAJI_BOARDVIEW_H
