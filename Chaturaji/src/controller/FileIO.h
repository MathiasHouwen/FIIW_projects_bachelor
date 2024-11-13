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

    int save(Game *game, QString filePath);
    void loadBoard(Game *game, QString filePath);

    static Piece jsonToPiece(const QJsonObject& jsonObject, Game* gamemodel);

private:
    static void jsonToBoard(QJsonObject boardObject, Game *gamemodel);

    static QJsonObject pieceToJson(const Piece* piece);
    static QJsonObject boardToJson(const Board *board);
    QJsonObject playerToJson(const Player *player);
    QJsonObject playersToJson(const Player *players, Player curr);

    QJsonDocument generateJson(Game *game);

    void jsonToPlayers(Game *game, QJsonObject players);
};

#endif //CHATURAJI_FILEIO_H