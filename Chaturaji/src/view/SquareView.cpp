#include "SquareView.h"
#include "PieceWidgit.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>

SquareView::~SquareView() {
}

QColor SquareView::getColor(QPair<QColor, QColor> colorPair) {
    return cell.x() % 2 ^ cell.y() % 2 ? colorPair.first : colorPair.second;
}

SquareView::SquareView(QWidget *parent, const QPoint &cell) : QWidget(parent), cell(cell) {
    pieceViewContainer = new QVBoxLayout(this);
    pieceViewContainer->setContentsMargins(2, 2, 2, 2);
    updateHighLight(HighLight::NONE);
}

void SquareView::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked(cell);
}

void SquareView::updatePiece(Piece *piece) {
    if (pieceView) {
        pieceViewContainer->removeWidget(pieceView);
        delete pieceView;  // Delete the old piece view
        pieceView = nullptr;
    }
    if (piece) {
        pieceView = new PieceWidgit(nullptr, piece);
        pieceViewContainer->addWidget(pieceView);
    }
}

void SquareView::setFillAndBorder(SquareView::HighLight highLighter) {
    fill = getColor(defaultColor);
    switch (highLighter) {
        case HighLight::NONE:border = Qt::transparent;break;
        case HighLight::SELECTSUGGEST: border = QCol::lightseagreen; break;
        case HighLight::MOVESUGGEST: border = QCol::cornflowerblue; break;
        case HighLight::HOVER:
            border = Qt::darkRed;
            fill = getColor(hoverColor);
            break;
        case HighLight::SELECTED:
            border = QCol::aquamarine;
            fill = getColor(selectedColor);
            break;
        case HighLight::ATTACKSUGGEST:
            border = QCol::tomato;
            fill = getColor(attackColor);
            break;
    }
}

void SquareView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    // fill
    QRect square(0, 0, width(), height());
    painter.fillRect(square, fill);
    //border
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(border);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(square);
}

void SquareView::updateHighLight(SquareView::HighLight highLighter) {
    setFillAndBorder(highLighter);
    update();
}

void SquareView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update(); // repaint
}

void SquareView::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    emit hoverUpdated(cell, true);
}

void SquareView::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    emit hoverUpdated(cell, false);
}





//SquareView::SquareView(QWidget *parent, QPoint cell, Game& model)
//    : QWidget(parent), cell(cell), model(model){
//    color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
//
//    pieceViewContainer = new QVBoxLayout(this);
//    pieceViewContainer->setContentsMargins(2,2,2,2);
//
//}
//    Piece* piece = model.getBoard().getCell(cell);
//    if (piece) {
//        if (!selection && piece->getPlayer() == model.getCurrentPlayer()
//            && (piece->getType() == model.getDice().first
//                || piece->getType() == model.getDice().second)) {
//            border = QColorConstants::Svg::lightseagreen;
//                }
//    }
//}

//void SquareView::paintEvent(QPaintEvent *event) {
//    QWidget::paintEvent(event);
//    getHighLight();
//    QPainter painter(this);
//    QRect square((width() - width()) / 2, (height() - height()) / 2, width(), height());
//    painter.fillRect(square, color);
//    QPen pen;
//    pen.setStyle(Qt::SolidLine);
//    pen.setColor(border);
//    pen.setWidth(5);
//    painter.setPen(pen);
//    painter.drawRect(square);
//
//    auto newPiece = model.getBoard().getCell(cell);
//    if (newPiece != piece) {
//        piece = newPiece;
//        if (pieceView) {
//            pieceViewContainer->removeWidget(pieceView);
//            delete pieceView;  // Delete the old piece view
//            pieceView = nullptr;
//        }
//        if (piece) {
//            pieceView = new PieceWidgit(nullptr, piece);
//            pieceViewContainer->addWidget(pieceView);
//        }
//    }
//}
//
//void SquareView::enterEvent(QEnterEvent *event) {
//    QWidget::enterEvent(event);
//    if (border == Qt::transparent) {
//        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::white : QColorConstants::Svg::blanchedalmond;
//        border = Qt::darkRed;
//    }
//
//    if (pieceView) {
//        pieceView->setHovered(true);
//    }
//    update();
//}

//void SquareView::leaveEvent(QEvent *event) {
//    QWidget::leaveEvent(event);
//
//    if (border == Qt::darkRed) {
//        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
//        border = Qt::transparent;
//    }
//
//    if (pieceView) {
//        pieceView->setHovered(false);
//    }
//    update();
//}


//void SquareView::getHighLight() {
//    if (border != Qt::darkRed) {
//        border = Qt::transparent;
//        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
//    }
//
//    QPoint* selection = model.getCurrentlySelectedCell();
//    if (selection && *selection == cell) {
//        border = QColorConstants::Svg::aquamarine;
//        color = QColorConstants::Svg::darkseagreen;
//    }
//    else if (selection && model.getPossibleMoves().contains(cell)) {
//        border = QColorConstants::Svg::lightseagreen;
//    }
//
//    Piece* piece = model.getBoard().getCell(cell);
//    if (piece) {
//        if (!selection && piece->getPlayer() == model.getCurrentPlayer()
//            && (piece->getType() == model.getDice().first
//                || piece->getType() == model.getDice().second)) {
//            border = QColorConstants::Svg::lightseagreen;
//                }
//    }
//}


//void SquareView::mouseReleaseEvent(QMouseEvent *event) {
//    QWidget::mouseReleaseEvent(event);
//
//    model.selectPiece(cell);
//    bool move = model.movePiece(cell);
//
//    if (move) {
//        model.advance();
//    }
//
//    getHighLight();
//    update();
//}

