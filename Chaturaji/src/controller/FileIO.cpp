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


FileIO::FileIO()= default;

// QFile(filepath)

void FileIO::loadBoard(Game* game, QString filePath){
    QFile file = QFile(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading:" << file.errorString();
    }

    QByteArray fileData = file.readAll();
    file.close();

    // JSON MAGIC
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject object = doc.object();
    FileIO::jsonToBoard(object, game);
}

Piece FileIO::jsonToPiece(const QJsonObject &jsonObject, Game *gamemodel) {

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

void FileIO::jsonToBoard(QJsonObject boardObject, Game* gamemodel){

    if (!boardObject.contains("board") || !boardObject["board"].isArray()) {
        qDebug() << "'board' key not found or is not an array in JSON.";
        return;
    }

    QJsonArray boardArray = boardObject["board"].toArray();
    Board& board = gamemodel->getBoard();

    for(int x=0; x<Board::getSize(); x++){
        QJsonArray rij = boardArray[x].toArray();
        for(int y=0; y<Board::getSize(); y++){
            QJsonObject pieceObj = rij[y].toObject();
            if (!pieceObj.isEmpty()) {
                Piece piece = FileIO::jsonToPiece(pieceObj, gamemodel);
                board.setCell(QPoint{x, y}, piece);
            }
        }
    }
}

// TODO: DIRECTION BUGS, ALWAYS X=0 Y=0
// ==========================
// == Saving functionality ==
// ==========================

QJsonObject FileIO::pieceToJson(const Piece* piece){
    QJsonObject jsonObject;
    if (piece != nullptr){
        jsonObject["type"] = Piece::getTypeName(piece->getType());
        jsonObject["player_colour"] = Player::getColourName(piece->getPlayer().getColour());

        QJsonObject dirobj;
        dirobj["x"] = piece->direction.x();
        dirobj["y"] = piece->direction.y();
        jsonObject["direction"] = dirobj;
    }
    return jsonObject;
}

QJsonObject FileIO::playerToJson(const Player* player){
    QJsonObject jsonObject;
    if (player != nullptr){
        jsonObject["naam"] = player->getName();
        jsonObject["colour"] = Player::getColourName(player->getColour());
        jsonObject["score"] = player->getScore();
    }
    return jsonObject;
}

QJsonObject FileIO::playersToJson(const Player* players, Player curr){
    QJsonObject jsonObject;
    QJsonArray playersJson;

    // TODO: REMOVE MAGIC NUMBER
    for (int i = 0; i<=3; i++){
        playersJson.append(playerToJson(&players[i]));
    }
    jsonObject["allPlayers"] = playersJson;
    jsonObject["currentPlayer"] = Player::getColourName(curr.getColour());

    return jsonObject;
}

QJsonObject FileIO::boardToJson(const Board* board){
    QJsonObject boardObject;
    QJsonArray boardArray;
    for(int x=0; x<Board::getSize(); x++){
        QJsonArray row;
        for(int y=0; y<Board::getSize(); y++){
            Piece* piece = board->getCell(QPoint(x, y));

            if (piece != nullptr){
                row.append(pieceToJson(piece));
            } else {
                row.append(QJsonValue::Null);
            }
        }
        boardArray.append(row);
    }
    boardObject["board"] = boardArray;
    return boardObject;
}


int FileIO::saveBoard(Game* game, QString filePath){
    QFile file = QFile(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return EXIT_FAILURE;
    }

    QJsonObject rootJsonObject;
    rootJsonObject["board"] = boardToJson(&(game->getBoard()))["board"];
    rootJsonObject["players"] = playersToJson(game->getPlayers(), game->getCurrentPlayer());
    QJsonDocument jsonDocument(rootJsonObject);

    file.write(jsonDocument.toJson());
    file.close();

    qDebug() << "File written successfully.";
    return 0; // Exit successfully
}