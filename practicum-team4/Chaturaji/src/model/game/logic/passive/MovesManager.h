//practicum 3:
// - Ebbe: class gemaakt
//     doel: facade om moves te maken met metadata zoals attack/normal en special rules
//      -> dingen hoeven niet meer validated te worden in bvb de Game class.
//          Alles wat van hier komt is al validated en "classified" met de juiste info
//      -> helpt game door logic te verminderen en controller voor highlight kleuren direct te mappen

#ifndef CHATURAJI_MOVESMANAGER_H
#define CHATURAJI_MOVESMANAGER_H


#include "../../enums_and_structs/ClassifiedMove.h"
#include "../../state/Board.h"
#include "PossibleMovesCalculator.h"
#include "SpecialRulesChecker.h"

#include <QSet>

class MovesManager {
private:
    Board& board;
    PossibleMovesCalculator calculator{board};
    SpecialRulesChecker rulesChecker{board};
    SpecialMoveType classifySpecialMove(Piece piece, QPoint destination);
public:
    explicit MovesManager(Board &board);
    QSet<ClassifiedMove> generateClassifiedMoves(Piece piece, QPoint location);
};


#endif //CHATURAJI_MOVESMANAGER_H
