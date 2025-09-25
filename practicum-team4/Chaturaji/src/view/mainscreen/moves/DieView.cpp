//
// Created by ebbew on 13-11-2024.
//
//volledig van Ebbe


#include <QFile>
#include "DieView.h"

DieView::DieView(QWidget *parent, int number) : QWidget(parent) {
    QFile svgFile(QString(ASSET_PATH) + "/dobbel.svg");
    svgFile.open(QIODevice::ReadOnly);
    QByteArray svgData = svgFile.readAll();
    svgFile.close();
    svgDOM.setContent(svgData);
    svg = new QSvgWidget(this);
    svg->load(svgDOM.toByteArray());
    setFixedSize(50,50);
    svg->setFixedSize(width(), height());
    updateNumber(number);
}

void DieView::updateNumber(int number) {
    QSet<QString> activeGroups = svgToggleGroups[number-1];
    auto groups = svgDOM.documentElement().elementsByTagName("g");
    for(int i=0; i<groups.size(); i++){
        auto group = groups.at(i).toElement();
        if(group.attribute("id") == "dots_and_edges") continue;
        if(activeGroups.contains(group.attribute("id")))
            group.setAttribute("visibility", "visible");
        else
            group.setAttribute("visibility", "hidden");
    }
    svg->load(svgDOM.toByteArray());
}

void DieView::updateDisabled(bool disabled) {
    auto group = svgDOM.documentElement().elementsByTagName("g").at(0).toElement();
    auto rect = svgDOM.documentElement().elementsByTagName("rect").at(0).toElement();
    group.setAttribute("fill", disabled ? "darkgray" : "black");
    rect.setAttribute("fill", disabled ? "lightgray" : "white");
    svg->load(svgDOM.toByteArray());
}
