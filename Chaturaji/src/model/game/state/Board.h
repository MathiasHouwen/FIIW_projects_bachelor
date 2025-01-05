// weinig veranderd in practicum 2
// enkel logica toegevoegd om piece in board te syncen met piece in player, en ook piece.cell door ebbe

#ifndef CHATURAJI_BOARD_H
#define CHATURAJI_BOARD_H

#include "../identities/Piece.h"
#include "../util/SquareDimension.h"
#include <QDebug>
#include <QPoint>
#include <QHash>

class Board {
private:
    QHash<QPoint, Piece> piecesMap{};
    static bool errorIfOutOfRane(const QPoint& cell);  // print error als een cell buiten het bord ligt

public:
    // is static const dus encapsulatie met getter heeft geen meerwaarde, daarom pulic
    static const SquareDimension dimension; // breedte/hoogte bord

    void putPieceAt(const QPoint& cell, Piece piece); // vul een cell met een piece (en delete eventuele oude piece)
    void clearCell(const QPoint& cell);
    void clear();   // delete alle pieces en vul bord met null

    [[nodiscard]] bool isEmptyAt(const QPoint& cell) const;    // kijkt of een cell geen piece heeft
    [[nodiscard]] std::optional<Piece> getPieceAt(const QPoint& cell) const;  // geeft de piece ptr in een cell

    [[nodiscard]] auto begin() const { return piecesMap.keys().cbegin(); }
    [[nodiscard]] auto end() const { return piecesMap.keys().cend(); }

};


#endif //CHATURAJI_BOARD_H
