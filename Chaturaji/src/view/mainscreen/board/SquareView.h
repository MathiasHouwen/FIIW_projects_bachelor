//
// Created by robin on 8/11/2024.
//
//door allemaal gemaakt en veranderd, alles vanaf piece view er in zit is door ebbe


#ifndef SQUAREVIEW_H
#define SQUAREVIEW_H
#include <qobjectdefs.h>
#include <qtmetamacros.h>
#include <QWidget>
#include <QBoxLayout>
#include <qgraphicsitem.h>
#include <QPainter>
#include <QPushButton>

#include "PieceWidgit.h"
#include "../../../model/game/oude_garbage/Game.h"

namespace QCol = QColorConstants::Svg;

class SquareView : public QWidget{
Q_OBJECT
public:
    enum class HighLight{NONE, HOVER, SELECTED, SELECTSUGGEST, MOVESUGGEST, ATTACKSUGGEST};
    ~SquareView() override;
    SquareView(QWidget *widget, const QPoint &cell);
    void updatePiece(BadPieceClass* piece);
    void updateHighLight(HighLight highLighter);
    void updateSetPieceGrey();

private:
    constexpr static QPair<QColor, QColor> defaultColor{QCol::beige, QCol::burlywood};
    constexpr static QPair<QColor, QColor> hoverColor{QCol::white, QCol::blanchedalmond};
    constexpr static QPair<QColor, QColor> selectedColor{QCol::lightgreen, QCol::darkseagreen};
    constexpr static QPair<QColor, QColor> attackColor{QCol::lightsalmon, QCol::lightcoral};

    QColor getColor(QPair<QColor, QColor> colorPair);
    void setFillAndBorder(SquareView::HighLight highLighter);

    const QPoint cell;
    QColor fill, border;
    QVBoxLayout* pieceViewContainer;
    PieceWidgit* pieceView{nullptr};

signals:
    void clicked(QPoint cell);
    void hoverUpdated(QPoint cell, bool hover);

protected:
    //mouse
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    //render
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};



#endif //SQUAREVIEW_H
