//
// Created by houwe on 10/11/2024.
//

#include "PlayerView.h"


PlayerView::PlayerView(const Player& player, QWidget *parent) : QWidget(parent) {
    color = QColor(Player::getColourName(player.getColour()));
    auto layout = new QVBoxLayout(this);

    nameLabel = new QLabel(player.getName());
    scoreLabel = new QLabel("Score: _");
    nameLabel->setContentsMargins(16, 0, 16, 0);
    scoreLabel->setContentsMargins(16, 0, 16, 0);

    layout->addWidget(nameLabel);
    layout->addWidget(scoreLabel);

    updateSetBigOrSmall(false);
}

void PlayerView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

    QPainterPath path;
    QRect boundingBox(0, 0, width(), height());
    path.addRoundedRect(boundingBox, 15, 15);  // Rounded corners with radius 15
    painter.fillPath(path, QColorConstants::Svg::grey);

    QPen strokePen;
    strokePen.setColor(color);
    strokePen.setWidth(10);
    painter.setPen(strokePen);
    painter.drawPath(path);
}

void PlayerView::updateScore(int score) {
    QString s;
    QTextStream ts(&s);
    ts << "Score: " << score;
    scoreLabel->setText(s);
}

void PlayerView::updateSetGrey() {
    color = QColorConstants::Svg::darkgray;
    update();
}

void PlayerView::updateSetBigOrSmall(bool big) {
    setMinimumHeight(big ? 250 : 0);
    nameLabel->setFont(QFont( "Arial", big ? 15 : 10, QFont::Bold));
    scoreLabel->setFont(QFont( "Arial", big ? 15 : 10, QFont::Bold));
    update();
}