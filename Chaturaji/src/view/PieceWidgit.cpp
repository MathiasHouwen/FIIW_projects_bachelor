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
    // color change voorbeeld: setSvgAttribute("fill", "green"); setSvgAttribute("stroke", "blue");
}

void PieceWidgit::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    svg->setFixedSize(width(), height());
}

void PieceWidgit::setHovered(bool hovered) {
    this->hovered = hovered;
    if(hovered) {
        svg->move(svg->x(), svg->y() - 4);
        setSvgAttribute("fill", "green");
        setSvgAttribute("stroke", "blue");
    }else{
        svg->move(svg->x(), svg->y() + 4);
        setSvgAttribute("fill", "red");
        setSvgAttribute("stroke", "black");
    }
}

void PieceWidgit::loadSvg() {
    QFile svgFile(QString(ASSET_PATH) + "/Chess_prg45.svg");
    svgFile.open(QIODevice::ReadOnly);
    QByteArray svgData = svgFile.readAll();
    svgFile.close();
    svgDOM.setContent(svgData);
}

void PieceWidgit::setSvgAttribute(QString name, QString value) {
    QDomElement pathNode = svgDOM.documentElement().elementsByTagName("path").at(0).toElement();
    pathNode.setAttribute(name, value);
    svg->load(svgDOM.toByteArray());
}
