//
// Created by houwe on 11/10/2024.
//

#include "FileIO.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


FileIO::FileIO(const QString &mFilePath) : m_filePath(mFilePath), m_file(mFilePath) {}

int FileIO::saveBoard(const Board* board) {
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << m_file.errorString();
        return EXIT_FAILURE;
    }

    QJsonDocument jsonDocument = generateJSONfile(board);
    m_file.write(jsonDocument.toJson());
    m_file.close();

    qDebug() << "File written successfully.";
    return 0; // Exit successfully
}

QJsonObject FileIO::pieceToJson(const Piece* piece){
    QJsonObject jsonObject;
    if (piece != nullptr){
        jsonObject["type"] = QString::fromStdString(Piece::getTypeName(piece->getType()));
        jsonObject["player_colour"] = Player::getColourName(piece->getPlayer().getMColour());

        QJsonObject dirobj;
        dirobj["x"] = piece->direction.x();
        dirobj["y"] = piece->direction.y();
        jsonObject["direction"] = dirobj;
    }
    return jsonObject;
}

QJsonDocument FileIO::generateJSONfile(const Board* board) {
    QJsonArray boardArray;

    for(int x=0; x<8; x++){
        QJsonArray row;
        for(int y=0; y<8; y++){
            Piece* piece = board->getCell(QPoint(x, y));

            if (piece != nullptr){
                row.append(pieceToJson(piece));
            } else {
                row.append(QJsonValue::Null);
            }
        }
        boardArray.append(row);
    }

    QJsonObject boardObject;
    boardObject["board"] = boardArray;
    QJsonDocument doc(boardObject);
    return doc;
}
