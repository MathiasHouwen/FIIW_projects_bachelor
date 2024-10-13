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
    int saveBoard(const Board* board);
    Board& loadBoard(Game* game);
    explicit FileIO(const QString &mFilePath);

    static Piece jsonToPiece(const QJsonObject& jsonObject, Game* gamemodel);


private:
    static QJsonObject pieceToJson(const Piece* piece);
    static QJsonDocument generateJSONfile(const Board* board);

    QString m_filePath;
    QFile m_file;

    static Board &jsonToBoard(QJsonObject boardObject, Game *gamemodel);
};

#endif //CHATURAJI_FILEIO_H