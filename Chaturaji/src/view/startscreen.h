//
// Created by robin on 14/11/2024.
//

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include "../view/MainWindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StartScreen; }
QT_END_NAMESPACE

class StartScreen : public QWidget {
Q_OBJECT

private slots:
    void on_pushButton_clicked();

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen() override;
    std::vector<std::string> getPlayers();
    void set_players(MainWindow* window);

private:
    Ui::StartScreen *ui;
    std::vector<std::string> players;
};


#endif //STARTSCREEN_H
