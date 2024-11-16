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
#include "../model/FileIO.h"
#include "PlayerView.h"
#include "FileIOView.h"
#include "../controller/Controller.h"
#include "DieView.h"
#include "DiceAndMovesView.h"
#include "PlayersView.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowIcon(QIcon(QString(ASSET_PATH) + "/Boat.svg"));

    auto boardView = new BoardView(ui->boardPanel);
    auto diceAndMovesView = new DiceAndMovesView(ui->turnsPanel);
    auto ioView = new FileIOView(model, ui->topBar);
    auto controller = new Controller(model, boardView, diceAndMovesView, ioView, playersView);
}

void MainWindow::makeSidePanel() {
    for (Player::colour color : { Player::colour::RED, Player::colour::BLUE, Player::colour::GREEN, Player::colour::YELLOW }) {
        auto player = new Player(color);
        player->setName(model.getPlayers()[static_cast<int>(color)].getName());
        auto playerView = new PlayerView(nullptr, player, &model);
        playersView->addPlayerFromColor(playerView, color);
    }
    ui->sidePanel->layout()->addWidget(playersView);
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

Game* MainWindow::getModel() {
    return &model;
}
