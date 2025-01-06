//practicum 3:
// - Ebbe: refactor voor nieuwe model classes compatibility

// volledig van mathias


#ifndef CHATURAJI_FILEIO_H
#define CHATURAJI_FILEIO_H

#include <qstring.h>
#include <QFile>
#include "../game/state/Board.h"
#include "../game/Game.h"

class FileIO {
public:
    explicit FileIO();

    int save(Game& game, QString filePath);
    void load(Game& game, QString filePath);


private:
    static void jsonToPlayers(Game& game, QJsonObject players);
    static void jsonToBoard(QJsonObject rootObj, Board& board);
    static Piece jsonToPiece(const QJsonObject& jsonObject);


    static QJsonObject pieceToJson(Piece piece);
    static QJsonArray boardToJson(Board& board);
    QJsonArray playersToJson(Game& game);

};

#endif //CHATURAJI_FILEIO_H