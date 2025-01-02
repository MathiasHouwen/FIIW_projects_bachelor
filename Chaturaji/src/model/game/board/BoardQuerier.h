//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_BOARDQUERIER_H
#define CHATURAJI_BOARDQUERIER_H


#include "Board.h"

class BoardQuerier {

private:
    Board& board;
public:
    void movePiece(QPoint fromCell, QPoint toCell);  // verplaats de piece van ene naar andere cell (oude cell wordt null)

};


#endif //CHATURAJI_BOARDQUERIER_H
