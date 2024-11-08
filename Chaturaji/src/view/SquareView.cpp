#include "SquareView.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

SquareView::SquareView(const Square& square, QWidget *parent)
    : QWidget(parent), square(square) {
    drawSquare();
}

SquareView::~SquareView() = default;

void SquareView::drawSquare() {
    setFixedSize(100, 100);

    auto *scene = new QGraphicsScene(this);

    scene->setSceneRect(QRect(0, 0, 100, 100));
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, Qt::white);

    auto *layout = new QVBoxLayout(this);
    auto w = new QWidget();
    w->setAutoFillBackground(true);
    w->setPalette(palette);
    w->setFixedSize(width(), height());
    layout->addWidget(w);
    setLayout(layout);
}
