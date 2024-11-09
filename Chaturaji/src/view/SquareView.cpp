#include "SquareView.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>



SquareView::SquareView(QWidget *parent, int xIndex, int yIndex)
    : QWidget(parent), xIndex(xIndex), yIndex(yIndex){
    color = xIndex % 2 ^ yIndex % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
}

SquareView::~SquareView() {

}

void SquareView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect square((width() - width()) / 2, (height() - height()) / 2, width(), height());
    painter.fillRect(square, color);
    if(border){
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::darkRed);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawRect(square);
    }
}

void SquareView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update(); // repaint
}

void SquareView::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);
    color = xIndex % 2 ^ yIndex % 2 ? QColorConstants::Svg::white : QColorConstants::Svg::blanchedalmond;
    border = true;
    update();
}

void SquareView::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    color = xIndex % 2 ^ yIndex % 2 ? QColorConstants::Svg::beige : QColorConstants::Svg::burlywood;
    border = false;
    update();
}
