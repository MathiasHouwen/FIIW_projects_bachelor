

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

class Board {
    private:
        static const int height = 8;
        static const int width = 8;
        bool board[width][height];

    public:
        void setCell(int row, int col, bool value);
        bool getCell(int row, int col);
        void move(int toRow, int toCol, int fromRow, int fromCol);
        int getHeight();
        void setAllTrue();
        int getWidth();
};


#endif //CHATURAJI_BOARD_H
