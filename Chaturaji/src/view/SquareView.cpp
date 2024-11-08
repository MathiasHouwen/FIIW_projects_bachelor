#include "SquareView.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

SquareView::SquareView(const Square& square, QWidget *parent, int index)
    : QWidget(parent), square(square) {
    drawSquare(index);
}

SquareView::~SquareView() = default;

void SquareView::drawSquare(int index) {
    setFixedSize(100, 100);

    auto *scene = new QGraphicsScene(this);

    scene->setSceneRect(QRect(0, 0, 100, 100));
    QPalette palette = QPalette();

    QColor beige(245, 245, 220);
    QColor brown(139, 69, 19);

    bool isDarkSquare = index % 2 == 1;
    if (isDarkSquare) {
        palette.setColor(QPalette::Window, brown);
    } else {
        palette.setColor(QPalette::Window, beige);
    }

    auto *layout = new QVBoxLayout(this);
    auto w = new QWidget();
    w->setAutoFillBackground(true);
    w->setPalette(palette);
    w->setFixedSize(width(), height());
    layout->addWidget(w);
    setLayout(layout);
}