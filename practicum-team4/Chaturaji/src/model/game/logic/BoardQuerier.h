//practicum 3:
// - Ebbe: class gemaakt, = extractie van oude Board class + extra functies
//     doel: high level logica zoals zoeken decouplen zodat de Board class enkel verantwoordelijk is voor state

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
    QSet<QPoint> getPiecesFromColor(Color color); // QList want ik was te lui om piece hashable te maken voor qset
    QSet<QPoint> getPiecesFromBoardHomeSide(HomeBoardSide homeSide);
    QSet<QPoint> getPiecesWithTypesAndColor(QSet<PieceType> types, Color color);
    bool isPointFromBoardSideEdge(QPoint cell, HomeBoardSide boardSide);
};


#endif //CHATURAJI_BOARDQUERIER_H
