//
// Created by houwe on 8/11/2024.
//

#ifndef CHATURAJI_PIECEWIDGIT_H
#define CHATURAJI_PIECEWIDGIT_H

#include <QWidget>
#include <QSvgWidget>
#include <QDomDocument>


class PieceWidgit : public QWidget {
Q_OBJECT

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QSvgWidget* svg;
    QDomDocument svgDOM;
    bool hovered{false};
    void loadSvg();
void setSvgAttribute(QString name, QString value);
public:
    void setHovered(bool hovered);
    explicit PieceWidgit(QWidget *parent = nullptr);
};



#endif //CHATURAJI_PIECEWIDGIT_H
