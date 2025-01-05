//
// Created by robin on 14/11/2024.
//

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include "../mainscreen/MainWindow.h"


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
    void set_players(MainWindow* window);

private:
    void getPlayers();
    QSet<QString> players{};
    Ui::StartScreen *ui;
};


#endif //STARTSCREEN_H
