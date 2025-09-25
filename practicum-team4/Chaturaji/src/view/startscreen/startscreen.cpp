//
// Created by robin on 14/11/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartScreen.h" resolved

#include "startscreen.h"

#include <iostream>
#include <ostream>

#include "ui_StartScreen.h"
#include "../../model/game/bots/AggressiveMoveStrategy.h"
#include "../../model/game/bots/PassiveMoveStrategy.h"


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
    getPlayers();
    set_players(w);
    w->startController();
    w->show();
    this->close();
}

void StartScreen::set_players(MainWindow* window) {

    for (QString name : players) {
        window->getGameController().addPlayer(name);
    }
    QString player4name = ui->player4Input->toPlainText();
    if(ui->agressive->isChecked()) {
        window->getGameController().addBot(player4name, std::make_shared<AggressiveMoveStrategy>());
    } else if(ui->passive->isChecked()) {
        window->getGameController().addBot(player4name, std::make_shared<PassiveMoveStrategy>());
    } else {
        window->getGameController().addPlayer(player4name);
    }

}

void StartScreen::getPlayers() {
    players.append(ui->player1Input->toPlainText());
    players.append(ui->player2Input->toPlainText());
    players.append(ui->player3Input->toPlainText());
}
