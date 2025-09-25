

//practicum 3:
// - Robin: class gemaakt en geschreven
// - Ebbe: refactor voor nieuwe model classes compatibility

#ifndef AGGRESSIVEMOVESTRATEGY_H
#define AGGRESSIVEMOVESTRATEGY_H



#include "MoveStrategy.h"
#include "../Game.h"

class AggressiveMoveStrategy : public MoveStrategy {
public:
    QPoint getNextMove(Game& game, const QSet<ClassifiedMove>& moves) override;
    QPoint getNextSelectedCell(Game& game, const QSet<QPoint>& selectables) override;

};



#endif //AGGRESSIVEMOVESTRATEGY_H
