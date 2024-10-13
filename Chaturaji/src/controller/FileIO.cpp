// volledig van mathias

#include "FileIO.h"
#include "../model/Game.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


FileIO::FileIO(const QString &mFilePath) : m_filePath(mFilePath), m_file(mFilePath) {}

Board& FileIO::loadBoard(Game* game){
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading:" << m_file.errorString();
    }

    QByteArray fileData = m_file.readAll();
    m_file.close();

    // JSON MAGIC
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject object = doc.object();
    return FileIO::jsonToBoard(object, game);
}

Piece FileIO::jsonToPiece(const QJsonObject &jsonObject, Game *gamemodel) {
    if (jsonObject.isEmpty()) return nullptr;

    QString typestr = jsonObject["type"].toString();
    Piece::Type type = Piece::getTypeFromName(typestr);

    QString colourstr = jsonObject["player_colour"].toString();
    Player::colour colour = Player::getColourFromName(colourstr);
    Player& player = gamemodel->getPlayerFromColour(colour);

    QJsonObject dirobj = jsonObject["direction"].toObject();
    int x = dirobj["x"].toInt();
    int y = dirobj["y"].toInt();
    QPoint direction(x, y);

    return Piece(type, direction, player);
}

Board& FileIO::jsonToBoard(QJsonObject boardObject, Game* gamemodel){
    QJsonArray boardArray = boardObject["Board"].toArray();

    Board& board = gamemodel->getBoard();

    for(int x=0; x<8; x++){
        QJsonArray rij = boardArray[x].toArray();
        for(int y=0; y<8; y++){
            QJsonObject pieceObj = rij[y].toObject();
            Piece piece = FileIO::jsonToPiece(pieceObj, gamemodel);
            board.setCell(QPoint{x, y}, piece);
        }
    }

    return board;
}

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
        jsonObject["player_colour"] = Player::getColourName(piece->getPlayer().getColour());

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

