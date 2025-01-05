//
// Created by houwe on 8/11/2024.
//
//volledig door mathias gemaakt natuurlijk. wie anders heeft zo erge dyslexie
// de svg bewerking logica met het DOM-documentmodel is wel door ebbe



#include <QVBoxLayout>
#include <iostream>
#include <QLabel>
#include <QPainter>
#include <QSvgRenderer>
#include <QFile>


#include "PieceWidgit.h"

QString PieceWidgit::pieceTypeToString(PieceType type) {
    switch (type) {
        case PieceType::PAWN: return "pawn";
        case PieceType::KING: return "king";
        case PieceType::ELEPHANT: return "elephant";
        case PieceType::HORSE: return "horse";
        case PieceType::BOAT: return "boat";
    }
}
QString PieceWidgit::ColorToString(Color color) {
    switch (color) {
        case Color::YELLOW: return "yellow";
        case Color::RED: return "red";
        case Color::BLUE: return "blue";
        case Color::GREEN: return "green";
    }
}

PieceWidgit::PieceWidgit(QWidget *parent, Piece piece)
    : QWidget(parent) {
    loadSvg(pieceTypeToString(piece.getType()));
    svg = new QSvgWidget(this);
    svg->load(svgDOM.toByteArray());
    setFill(ColorToString(piece.getColor()));
    setStroke(QColorConstants::Svg::black);
}

PieceWidgit::PieceWidgit(QWidget *parent, PieceType type)
    : QWidget(parent) {
    loadSvg(pieceTypeToString(type));
    svg = new QSvgWidget(this);
    svg->load(svgDOM.toByteArray());
    setFill(Qt::gray);
    setStroke(Qt::white);
}


void PieceWidgit::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    svg->setFixedSize(width(), height());
}

void PieceWidgit::setHovered(bool hovered) {
    this->hovered = hovered;
    if(hovered) {
        svg->move(svg->x(), svg->y() - 4);
        setStroke(QColorConstants::Svg::gray);
    }else{
        svg->move(svg->x(), svg->y() + 4);
        setStroke(QColorConstants::Svg::black);
    }
}

void PieceWidgit::loadSvg(QString name) {
    QFile svgFile(QString(ASSET_PATH) + "/" + name + ".svg");
    svgFile.open(QIODevice::ReadOnly);
    QByteArray svgData = svgFile.readAll();
    svgFile.close();
    svgDOM.setContent(svgData);
}

void PieceWidgit::setSvgAttribute(QString name, QString value) {
    QDomElement pathNode = svgDOM.documentElement().elementsByTagName("g").at(0).toElement();
    pathNode.setAttribute(name, value);
    svg->load(svgDOM.toByteArray());
}

void PieceWidgit::setStroke(QColor color) {
    setSvgAttribute("stroke", color.name());
}

void PieceWidgit::setFill(QColor color) {
    setSvgAttribute("fill", color.name());
}

void PieceWidgit::setGray() {
    setFill(QColorConstants::Svg::lightslategray);
    setStroke(QColorConstants::Svg::darkslategray);
}
