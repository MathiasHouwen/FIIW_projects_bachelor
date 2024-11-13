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
#include "FileIOView.h"
#include "../controller/Controller.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    connect(&model, &Game::somethingChanged, this, &MainWindow::setText);
    ui->setupUi(this);

    FileIO io;
    io.loadBoard(&model, "../startingFile.txt");

    auto boardView = new BoardView(ui->boardPanel);
    auto controller = new Controller(model, boardView);

//    auto player = new Player(Player::colour::RED);
//    auto playerView = new PlayerView(nullptr, player);
//    ui->sidePanel->layout()->addWidget(playerView);
    for (Player::colour color : { Player::colour::RED, Player::colour::BLUE, Player::colour::GREEN, Player::colour::YELLOW }) {
        auto player = new Player(color);
        auto playerView = new PlayerView(nullptr, player);
        ui->sidePanel->layout()->addWidget(playerView);
    }

    auto ioView = new FileIOView(model, ui->topBar);


    model.doubleDobbel();
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
}

void MainWindow::setText() {
    ui->debugLabel->clear();
    QString s;
    QTextStream t(&s);
    t << "player: {col: " << Player::getColourName(model.getCurrentPlayer().getColour());
    t << ", name: " << model.getCurrentPlayer().getName();
    t << ", score: " << model.getCurrentPlayer().getScore() << "}";
    t << "  |   move:" << model.getMove();
    t << "  |   dice: [" << Piece::getTypeName(model.getDice().first) << ", " << Piece::getTypeName(model.getDice().second) << "]";
    ui->debugLabel->setText(s);
}