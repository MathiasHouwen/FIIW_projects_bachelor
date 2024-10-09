

#include <iostream>
#include "Game.h"
#include "Piece.h"

Game::Game() : board() {

    QPoint testCell = {4,3};
    Piece testPiece(Piece::Type::PAWN);
    PatternMover mover(board);
    setCell(testCell, true);
    QSet<QPoint> moves = mover.getPossibleMoves(testPiece.getAttackPattern(), testCell);
    for(QPoint p : moves){
        std::cout << p.x() << ", "<<p.y() << std::endl;
        setCell(p, true);
    }

}

const Board& Game::getBoard() const {
    return board;
}
void Game::setCell(QPoint cell, bool value) {
    board.setCell(cell, value);
}