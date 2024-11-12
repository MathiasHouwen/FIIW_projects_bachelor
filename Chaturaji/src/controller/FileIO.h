//
// Created by houwe on 11/10/2024.
//

#ifndef CHATURAJI_FILEIO_H
#define CHATURAJI_FILEIO_H

#include <qstring.h>
#include <QFile>
#include "../model/Board.h"
#include "../model/Game.h"

class FileIO {
public:
    explicit FileIO();

    int saveBoard(const Board* board, QString filePath);
    void loadBoard(Game *game, QString filePath);

    static Piece jsonToPiece(const QJsonObject& jsonObject, Game* gamemodel);

private:
    static QJsonObject pieceToJson(const Piece* piece);
    static QJsonDocument generateJSONfile(const Board* board);

    static void jsonToBoard(QJsonObject boardObject, Game *gamemodel);

    QJsonObject playersToJson();

    QJsonObject playerToJson();
};

#endif //CHATURAJI_FILEIO_H