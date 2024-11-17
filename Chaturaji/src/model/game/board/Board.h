// weinig veranderd in practicum 2
// enkel logica toegevoegd om piece in board te syncen met piece in player, en ook piece.cell door ebbe

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include "Piece.h"

class Board {
private:
    static constexpr int size = 8;  // breedte/hoogte bord
    static void errorIfOutOfRane(QPoint cell);  // print error als een cell buiten het bord ligt

    Piece* board[size][size];   // bord. Elke cell is een pointer naar een piece op de heap. lege cell = null

public:
    static bool isInRange(QPoint cell); // kijkt of een cell binnen het bord ligt
    static constexpr int getSize(){return size;};  // getter. ALs die in de c++ file ge-implement is, dan wordt die niet meer gezien als const

    void setCell(QPoint cell, Piece value); // vul een cell met een piece (en delete eventuele oude piece)
    void move(QPoint fromCell, QPoint toCell);  // verplaats de piece van ene naar andere cell (oude cell wordt null)
    void clear();   // delete alle pieces en vul bord met null

    bool isCellEmpty(QPoint cell) const;    // kijkt of een cell geen piece heeft
    Piece* getCell(QPoint cell) const;  // geeft de piece ptr in een cell

};


#endif //CHATURAJI_BOARD_H
