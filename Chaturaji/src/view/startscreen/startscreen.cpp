//
// Created by robin on 14/11/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartScreen.h" resolved

#include "startscreen.h"

#include <iostream>
#include <ostream>

#include "ui_StartScreen.h"


StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent), ui(new Ui::StartScreen) {
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this,&StartScreen::on_pushButton_clicked);
}

StartScreen::~StartScreen() {
    delete ui;
}

void StartScreen::on_pushButton_clicked() {
    auto *w = new MainWindow();
    set_players(w);
    w->startController();
    w->show();
    this->close();
}

void StartScreen::set_players(MainWindow* window) {

    for (QString name : players) {
        window->getGameController().getGame().getGameState().addPlayer(name, PlayerType::HUMAN);
    }
//    if(ui->agressive->isChecked()) {
//        window->getModel()->makeBot(Player::colour::BLUE, true);
//    }
//    if(ui->passive->isChecked()) {
//        window->getModel()->makeBot(Player::colour::GREEN, false);
//    }
}

void StartScreen::getPlayers() {
    players.insert(ui->player1Input->toPlainText());
    players.insert(ui->player2Input->toPlainText());
    players.insert(ui->player3Input->toPlainText());
    players.insert(ui->player4Input->toPlainText());
}
