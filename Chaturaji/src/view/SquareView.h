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

namespace QCol = QColorConstants::Svg;

class SquareView : public QWidget{
Q_OBJECT
public:
    enum class HighLight{NONE, HOVER, SELECTED, SELECTSUGGEST, MOVESUGGEST, ATTACKSUGGEST};
    ~SquareView() override;
    SquareView(QWidget *widget, const QPoint &cell);
    void updatePiece(Piece* piece);
    void updateHighLight(HighLight highLighter);

private:
    constexpr static QPair<QColor, QColor> defaultColor{QCol::beige, QCol::burlywood};
    constexpr static QPair<QColor, QColor> hoverColor{QCol::white, QCol::blanchedalmond};
    constexpr static QPair<QColor, QColor> selectedColor{QCol::lightgreen, QCol::darkseagreen};
    constexpr static QPair<QColor, QColor> attackColor{QCol::lightsalmon, QCol::lightcoral};
    QColor getColor(QPair<QColor, QColor> colorPair);
    QPair<QColor, QColor> getFillAndBorder(SquareView::HighLight highLighter);

    const QPoint cell;
    QVBoxLayout* pieceViewContainer;
    PieceWidgit* pieceView{nullptr};

signals:
    void clicked(QPoint cell);

//    Game& model;
//    Piece* piece{nullptr};
//    PieceWidgit* pieceView{nullptr};
//    QVBoxLayout* pieceViewContainer;
//    void getHighLight();
//explicit SquareView(QWidget *parent, QPoint cell, Game& model);

protected:
    void mousePressEvent(QMouseEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;
//    void enterEvent(QEnterEvent *event) override;
//    void leaveEvent(QEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
//
//    void mouseReleaseEvent(QMouseEvent *event) override;
};



#endif //SQUAREVIEW_H
