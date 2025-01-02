//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_BOARDQUERIER_H
#define CHATURAJI_BOARDQUERIER_H


#include "Board.h"
#include <qDebug>

class BoardQuerier {

private:
    Board& board;
public:
    std::optional<Piece> movePiece(QPoint fromCell, QPoint toCell);  // verplaats de piece van ene naar andere cell (oude cell wordt null)
    QList<Piece> getPiecesFromColor(Color color);
};


#endif //CHATURAJI_BOARDQUERIER_H
