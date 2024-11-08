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
#include "PieceView.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

//    auto b = new BoardView(this);

//    auto m_scene = new QGraphicsScene(this);
//    auto m_view = new QGraphicsView(m_scene, this);
//    auto rect = new QGraphicsRectItem(10,10,100,100);
//    rect->setBrush(QBrush(Qt::darkRed));
//    m_scene->addItem(rect);

    // Create the main layout for MainWindow
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create and add BoardView to the layout
    auto boardView = new BoardView(this);
    mainLayout->addWidget(boardView);

    // Create and add PieceView to the layout
    auto pieceView = new PieceView(this);
    mainLayout->addWidget(pieceView);

    // Set the layout for MainWindow
    this->setLayout(mainLayout);

}

MainWindow::~MainWindow() {
    delete ui;
}
