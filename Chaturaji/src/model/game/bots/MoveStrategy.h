
#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

//practicum 3:
// - Robin: class gemaakt en geschreven

#include <QSet>
#include <QPoint>

class Game;
struct ClassifiedMove;
class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    virtual QPoint getNextMove(Game& game, const QSet<ClassifiedMove>& moves) = 0;
    virtual QPoint getNextSelectedCell(Game& game, const QSet<QPoint>& selectables) = 0;

};



#endif //MOVESTRATEGY_H
