//
// Created by robin on 16/11/2024.
//
//volledig van robin, kleine refactors door ebbe


#ifndef PLAYERSVIEW_H
#define PLAYERSVIEW_H
#include <QVBoxLayout>
#include <QWidget>
#include "PlayerView.h"


class PlayersView: public QWidget{
Q_OBJECT
public:
    explicit PlayersView(QWidget *parent = nullptr);
    ~PlayersView() override;
    void addPlayerView(const Player& player);

    void updateScore(Color color, int score);
    void updateSetBigAndToTop(Color color);
    void updateSetGrey(Color color);
    void clear();

private:
    QMap<Color, PlayerView*> players;
    PlayerView* bigPlayer{nullptr};
    QVBoxLayout* layout;
};



#endif //PLAYERSVIEW_H
