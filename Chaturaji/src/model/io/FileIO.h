//
// Created by houwe on 11/10/2024.
//

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

    //int save(Game& game, QString filePath);
    void load(Game& game, QString filePath);

    static Piece jsonToPiece(const QJsonObject& jsonObject);

private:
    static QString pieceTypeToString(PieceType type);
    static QString ColorToString(Color color);
    static QString homeBoardSideToString(HomeBoardSide side);

    static PieceType pieceTypeFromString(QString type);
    static Color ColorFromString(QString color);
    static HomeBoardSide homeBoardSideFromString(QString side);

    static void jsonToBoard(QJsonObject rootObj, Board& board);
    static QJsonObject pieceToJson(Piece piece);

    static QJsonObject boardToJson(Board& board);
//    QJsonObject playerToJson(const std::shared_ptr<Player> *player);
//    QJsonObject playersToJson(const std::shared_ptr<Player> *players, Player curr);

//    QJsonDocument generateJson(Game *game);

    static void jsonToPlayers(Game& game, QJsonObject players);
};

#endif //CHATURAJI_FILEIO_H