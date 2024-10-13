//
// Created by houwe on 11/10/2024.
//

#ifndef CHATURAJI_FILEIO_H
#define CHATURAJI_FILEIO_H

#include <qstring.h>
#include <QFile>
#include "../model/Board.h"

class FileIO {
public:
    int saveBoard();
    Board loadBoard();
    explicit FileIO(const QString &mFilePath);
private:
    static QJsonObject pieceToJson(const Piece* piece);
    void generateJSONfile(Board board);
    QString m_filePath;
    QFile m_file;
};

#endif //CHATURAJI_FILEIO_H