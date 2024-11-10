//
// Created by ebbew on 7-11-2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BoardView.h"
#include "SquareView.h"
#include "PieceWidgit.h"
#include "../controller/FileIO.h"
#include "PlayerView.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    FileIO io{"../startingFile.txt"};
    io.loadBoard(&model);

//    auto boardView = new BoardView(model, ui->boardPanel);
    auto player = new Player(Player::colour::RED);
    auto playerView = new PlayerView(ui->boardPanel, player);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    makeBoardPanelShapeSquare();
}

void MainWindow::makeBoardPanelShapeSquare() {
    auto boardPanel = ui->boardPanel;
    boardPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    int width = boardPanel->width();
    int height = boardPanel->height();
    int size = qMin(width, height);
    int x = boardPanel->x() + (width - size) / 2;
    int y = boardPanel->y() + (height - size) / 2;
    boardPanel->setGeometry(x, y, size, size);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    makeBoardPanelShapeSquare();
    QString s;
    QTextStream t(&s);
    t << "player: {col: " << Player::getColourName(model.getCurrentPlayer().getColour());
    t << ", name: " << model.getCurrentPlayer().getName();
    t << ", score: " << model.getCurrentPlayer().getScore() << "}";
    t << "  |   move:" << model.getMove();
    t << "  |   dice: [" << Piece::getTypeName(model.getDice().first) << ", " << Piece::getTypeName(model.getDice().second) << "]";
    ui->debugLabel->setText(s);
}
