#include "SquareView.h"
#include "PieceWidgit.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>


SquareView::SquareView(QWidget *parent, QPoint cell, Game& model)
    : QWidget(parent), cell(cell), model(model){
    color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;

    pieceContainer = new QVBoxLayout(this);
    pieceContainer->setContentsMargins(2,2,2,2);

}

SquareView::~SquareView() {

}

void SquareView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    getHighLight();
    QPainter painter(this);
    QRect square((width() - width()) / 2, (height() - height()) / 2, width(), height());
    painter.fillRect(square, color);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(border);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(square);

    auto newPiece = model.getBoard().getCell(cell);
    if (newPiece != piece) {
        piece = newPiece;
        if (pieceView) {
            pieceContainer->removeWidget(pieceView);
            delete pieceView;  // Delete the old piece view
            pieceView = nullptr;
        }
        if (piece) {
            pieceView = new PieceWidgit(nullptr, piece);
            pieceContainer->addWidget(pieceView);
        }
    }
}

void SquareView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update(); // repaint
}

void SquareView::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    if (border == Qt::transparent) {
        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::white : QColorConstants::Svg::blanchedalmond;
        border = Qt::darkRed;
    }

    if (pieceView) {
        pieceView->setHovered(true);
    }
    update();
}

void SquareView::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);

    if (border == Qt::darkRed) {
        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
        border = Qt::transparent;
    }

    if (pieceView) {
        pieceView->setHovered(false);
    }
    update();
}


void SquareView::getHighLight() {
    if (border != Qt::darkRed) {
        border = Qt::transparent;
        color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
    }

    QPoint* selection = model.getCurrentlySelectedCell();
    if (selection && *selection == cell) {
        border = QColorConstants::Svg::aquamarine;
        color = QColorConstants::Svg::darkseagreen;
    }
    else if (selection && model.getPossibleMoves().contains(cell)) {
        border = QColorConstants::Svg::lightseagreen;
    }

    Piece* piece = model.getBoard().getCell(cell);
    if (piece) {
        if (!selection && piece->getPlayer() == model.getCurrentPlayer()
            && (piece->getType() == model.getDice().first
                || piece->getType() == model.getDice().second)) {
            border = QColorConstants::Svg::lightseagreen;
                }
    }
}


void SquareView::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);

    model.selectPiece(cell);
    bool move = model.movePiece(cell);

    if (move) {
        model.advance();
    }

    getHighLight();
    update();
}

