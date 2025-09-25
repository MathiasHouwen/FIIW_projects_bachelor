// taakverdeling: zie h-file


#include "PassiveMoveStrategy.h"

QPoint PassiveMoveStrategy::getNextMove(Game& game, const QSet<ClassifiedMove>& moves) {
    // return random (eerste)
    for(auto move : moves) return move.destination;
}

QPoint PassiveMoveStrategy::getNextSelectedCell(Game &game, const QSet<QPoint> &selectables) {
    QHash<PieceType, QPoint> pieceTypes;
    for(auto cell : selectables){
        auto type = game.getGameState().getBoard().getPieceAt(cell)->getType();
        pieceTypes[type] = cell;
    }
    // pak pieces die niet veel bewegen
    if(pieceTypes.contains(PieceType::PAWN)) return pieceTypes[PieceType::PAWN];
    if(pieceTypes.contains(PieceType::KING)) return pieceTypes[PieceType::KING];
    // anders pak "random" (eerste die je kan vinden)
    for(auto cell : pieceTypes) return cell;
}
