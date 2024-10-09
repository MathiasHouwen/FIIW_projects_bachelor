

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include <QPoint>

class Board {
    private:
        static const int size = 8;
        bool board[size][size];

    public:
        void setCell(int row, int col, bool value);
        bool isCellEmpty(QPoint cell);
        bool getCell(int row, int col);
        void move(int toRow, int toCol, int fromRow, int fromCol);
        void setAllTrue();
        bool isInRange(QPoint cell);

    static const int getSize();
};


#endif //CHATURAJI_BOARD_H
