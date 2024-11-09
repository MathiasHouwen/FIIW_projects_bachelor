//
// Created by houwe on 8/11/2024.
//

#include <QVBoxLayout>
#include <iostream>
#include <QLabel>
#include <QPainter>
#include <QSvgRenderer>
#include <QFile>


#include "PieceWidgit.h"

PieceWidgit::PieceWidgit(QWidget *parent)
        : QWidget(parent) {

    loadSvg();
    svg = new QSvgWidget(this);
    svg->load(svgDOM.toByteArray());
    setFill(QColorConstants::Svg::lightseagreen);
    setStroke(QColorConstants::Svg::black);
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

void PieceWidgit::loadSvg() {
    QFile svgFile(QString(ASSET_PATH) + "/boat.svg");
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
