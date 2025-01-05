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
#include "board/BoardView.h"
#include "board/SquareView.h"
#include "board/PieceWidgit.h"
#include "../../model/io/FileIO.h"
#include "player/PlayerView.h"
#include "toolbar/FileIOView.h"
#include "../../controller/Controller.h"
#include "moves/DieView.h"
#include "moves/DiceAndMovesView.h"
#include "player/PlayersView.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowIcon(QIcon(QString(ASSET_PATH) + "/boat.svg"));

    auto boardView = new BoardView(ui->boardPanel);
    auto diceAndMovesView = new DiceAndMovesView(ui->turnsPanel);
    auto ioView = new FileIOView(ui->topBar);
    auto playersView = new PlayersView(ui->sidePanel);
    controller = new Controller(gameController, boardView, diceAndMovesView, ioView, playersView);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    makeBoardPanelShapeSquare();
}

// gewoon voor responsive design: board zal de maximale mogelijke grootte innemen terwijl een 1:1 aspect ratio behouden wordt
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

GameController &MainWindow::getGameController() {
    return gameController;
}

void MainWindow::startController() {
    controller->start();
}
