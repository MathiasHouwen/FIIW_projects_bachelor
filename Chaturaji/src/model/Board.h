

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include <QPoint>
#include "Piece.h"

class Board {
    private:
        static const int size = 8;
        Piece board[size][size];
        static void errorIfOutOfRane(QPoint cell);

    public:
        void setCell(QPoint cell, const Piece &value);
        bool isCellEmpty(QPoint cell);
        Piece getCell(QPoint cell);
        void move(QPoint fromCell, QPoint toCell);
        void setAllTrue();

        static bool isInRange(QPoint cell);

    static const int getSize();
};


#endif //CHATURAJI_BOARD_H
