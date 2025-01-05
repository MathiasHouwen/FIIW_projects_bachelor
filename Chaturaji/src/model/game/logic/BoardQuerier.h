//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_BOARDQUERIER_H
#define CHATURAJI_BOARDQUERIER_H


#include "../state/Board.h"
#include <QDebug>

class BoardQuerier {

private:
    Board& board;
public:
    explicit BoardQuerier(Board &board);

    std::optional<Piece> movePiece(QPoint fromCell, QPoint toCell);  // verplaats de piece van ene naar andere cell (oude cell wordt null)
    QList<Piece> getPiecesFromColor(Color color); // QList want ik was te lui om piece hashable te maken voor qset
    QList<Piece> getPiecesFromBoardHomeSide(HomeBoardSide homeSide);
};


#endif //CHATURAJI_BOARDQUERIER_H
