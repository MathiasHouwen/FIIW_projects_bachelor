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

    auto container = new QVBoxLayout(this);
    container->setContentsMargins(2,2,2,2);
    Piece* piece = model.getBoard().getCell(cell);
    if(piece){
        pieceView = new PieceWidgit(nullptr, piece);
        container->addWidget(pieceView);
    }
}

SquareView::~SquareView() {

}

void SquareView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect square((width() - width()) / 2, (height() - height()) / 2, width(), height());
    painter.fillRect(square, color);
    QPen pen;
    getHighLight();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(border);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(square);
}

void SquareView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update(); // repaint
}

void SquareView::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::white : QColorConstants::Svg::blanchedalmond;
    border = Qt::darkRed;
    if(pieceView)
        pieceView->setHovered(true);
    update();
}

void SquareView::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    color = cell.x() % 2 ^ cell.y() % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
    border = Qt::transparent;
    if(pieceView)
        pieceView->setHovered(false);
    update();
}

void SquareView::getHighLight() {
    if(border != Qt::transparent) return;
    QPoint* selection = model.getCurrentlySelectedCell();
    if(selection && *selection == cell)
        border = QColorConstants::Svg::aquamarine;
    else if(selection && model.getPossibleMoves().contains(cell))
        border = QColorConstants::Svg::lightseagreen;

    Piece* piece = model.getBoard().getCell(cell);
    if(piece){
        if(!selection && piece->getPlayer() == model.getCurrentPlayer()
           && (piece->getType() == model.getDice().first
               || piece->getType() == model.getDice().second)){
            border = QColorConstants::Svg::lightseagreen;
        }
    }
}
