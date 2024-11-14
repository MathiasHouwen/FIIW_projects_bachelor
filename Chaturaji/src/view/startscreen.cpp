//
// Created by robin on 14/11/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartScreen.h" resolved

#include "startscreen.h"

#include <iostream>
#include <ostream>
#include <ui_MainWindow.h>

#include "ui_StartScreen.h"


StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent), ui(new Ui::StartScreen) {
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

StartScreen::~StartScreen() {
    delete ui;
}

void StartScreen::on_pushButton_clicked() {
    this->close();
    auto *w = new MainWindow();
    set_players(w);
    w->show();
}

void StartScreen::set_players(MainWindow* window) {
    players.push_back(ui->player1Input->toPlainText().toStdString());
    players.push_back(ui->player2Input->toPlainText().toStdString());
    players.push_back(ui->player3Input->toPlainText().toStdString());
    players.push_back(ui->player4Input->toPlainText().toStdString());
    for (int i = 0; i < players.size(); i++) {
        window->getModel().setPlayerName(players[i].data(), static_cast<Player::colour>(i));
    }
}
