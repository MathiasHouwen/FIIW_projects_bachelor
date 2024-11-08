//
// Created by ebbew on 7-11-2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BoardView.h"
#include "PieceView.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto b = new BoardView(this);

//    auto m_scene = new QGraphicsScene(this);
//    auto m_view = new QGraphicsView(m_scene, this);
//    auto rect = new QGraphicsRectItem(10,10,100,100);
//    rect->setBrush(QBrush(Qt::darkRed));
//    m_scene->addItem(rect);

}

MainWindow::~MainWindow() {
    delete ui;
}
