

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include <QPoint>

class Board {
    private:
        static const int size = 8;
        bool board[size][size];
        void errorIfOutOfRane(QPoint cell);

    public:
        void setCell(QPoint cell, bool value);
        bool isCellEmpty(QPoint cell);
        bool getCell(QPoint cell);
        void move(QPoint fromCell, QPoint toCell);
        void setAllTrue();
        bool isInRange(QPoint cell);

    static const int getSize();
};


#endif //CHATURAJI_BOARD_H
