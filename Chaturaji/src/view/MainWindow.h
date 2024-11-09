//
// Created by ebbew on 7-11-2024.
//

#ifndef CHATURAJI_MAINWINDOW_H
#define CHATURAJI_MAINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
protected:
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    void makeBoardPanelShapeSquare();
};


#endif //CHATURAJI_MAINWINDOW_H
