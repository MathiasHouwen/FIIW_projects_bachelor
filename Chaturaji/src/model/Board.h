

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include "Piece.h"

class Board {
    private:
        static const int size = 8;
        Piece*board[size][size] = {};
        static void errorIfOutOfRane(QPoint cell);

    public:
        void setCell(QPoint cell, Piece *value);
        [[nodiscard]] bool isCellEmpty(QPoint cell) const;
        [[nodiscard]] Piece* getCell(QPoint cell) const;
        void move(QPoint fromCell, QPoint toCell);
        void setAllNull();
        static bool isInRange(QPoint cell);
        static int getSize();
};


#endif //CHATURAJI_BOARD_H
