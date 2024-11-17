//
// Created by houwe on 8/11/2024.
//

#ifndef CHATURAJI_PIECEWIDGIT_H
#define CHATURAJI_PIECEWIDGIT_H

#include <QWidget>
#include <QSvgWidget>
#include <QDomDocument>
#include "../../../model/game/board/Piece.h"


class PieceWidgit : public QWidget {
Q_OBJECT

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QSvgWidget* svg;
    QDomDocument svgDOM;
    bool hovered{false};
    void loadSvg(QString name);
    void setSvgAttribute(QString name, QString value);
    void setFill(QColor color);
    void setStroke(QColor color);
public:
    PieceWidgit(QWidget *parent, Piece* piece);
    PieceWidgit(QWidget *parent, Piece::Type type);
    void setHovered(bool hovered);
    void setGray();
};



#endif //CHATURAJI_PIECEWIDGIT_H
