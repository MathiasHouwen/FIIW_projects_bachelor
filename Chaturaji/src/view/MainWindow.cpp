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


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // QVBox layout maakt positie relatief
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // TODO: QUICK DIRTY CODE IEUW, so many magic numbers jezus
    // TODO: MAAK DIT APARTE WIDGIT CLASS
    int index = 0;
    for(int col=0; col<8; col++) {
        for (int rij = 0; rij < 8; rij++) {
            Square square{100 * rij, 100*col, nullptr};
            auto s = new SquareView(square, this, index);
            s->move(92 * rij, 92 * col);
            index++;
        }
        index++;
    }

//    Square square{30, 40, nullptr};
//    auto s = new SquareView(square, this);
//    mainLayout->addWidget(s);

    auto boardView = new BoardView(this);
    mainLayout->addWidget(boardView);

    auto pw1 = new PieceWidgit(this);
    auto pw2 = new PieceWidgit(this);

    mainLayout->addWidget(pw1);
    mainLayout->addWidget(pw2);
}

MainWindow::~MainWindow() {
    delete ui;
}
