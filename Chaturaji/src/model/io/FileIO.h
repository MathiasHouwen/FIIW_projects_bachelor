//
// Created by houwe on 11/10/2024.
//

// volledig van mathias

#ifndef CHATURAJI_FILEIO_H
#define CHATURAJI_FILEIO_H

#include <qstring.h>
#include <QFile>
#include "../game/board/Board.h"
#include "../game/Game.h"

class FileIO {
public:
    explicit FileIO();

    int save(Game *game, QString filePath);
    void loadBoard(Game *game, QString filePath);

    static BadPieceClass jsonToPiece(const QJsonObject& jsonObject, Game* gamemodel);

private:
    static void jsonToBoard(QJsonObject boardObject, Game *gamemodel);

    static QJsonObject pieceToJson(const BadPieceClass* piece);
    static QJsonObject boardToJson(const Board *board);
    QJsonObject playerToJson(const std::shared_ptr<Player> *player);
    QJsonObject playersToJson(const std::shared_ptr<Player> *players, Player curr);

    QJsonDocument generateJson(Game *game);

    void jsonToPlayers(Game *game, QJsonObject players);
};

#endif //CHATURAJI_FILEIO_H