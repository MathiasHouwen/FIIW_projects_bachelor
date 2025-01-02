// volledig van mathias
// nog steeds volledig van mathias

#include "FileIO.h"
#include "../game/Game.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


FileIO::FileIO()= default;

// ===========================
// == Loading functionality ==
// ===========================

BadPieceClass FileIO::jsonToPiece(const QJsonObject &jsonObject, Game *gamemodel) {
    QString typestr = jsonObject["type"].toString();
    BadPieceClass::Type type = BadPieceClass::getTypeFromName(typestr);

    QString colourstr = jsonObject["player_colour"].toString();
    Player::colour colour = Player::getColourFromName(colourstr);
    Player& player = gamemodel->getPlayerFromColour(colour);

    QJsonObject dirobj = jsonObject["direction"].toObject();
    int x = dirobj["x"].toInt();
    int y = dirobj["y"].toInt();
    QPoint direction(x, y);

    return BadPieceClass(type, direction, player);
}

void FileIO::jsonToPlayers(Game* game, QJsonObject rootObj){
    if (!rootObj.contains("players")) {
        qDebug() << "'players' key not found in playerObject";
        return;
    }
    if (!rootObj["players"].isObject()){
        qDebug() << "'players' is not an object in JSON.";
        return;
    }

    QJsonObject playersObj = rootObj["players"].toObject();
    QJsonArray allPlayersArray = playersObj["allPlayers"].toArray();
    for (const QJsonValue& playerVal : allPlayersArray) {
        QJsonObject playerObj = playerVal.toObject();

        QString colourStr = playerObj["colour"].toString();
        Player::colour colour = Player::getColourFromName(colourStr);

        QString naam = playerObj["naam"].toString();
        game->setPlayerName(naam, colour);

        int score = playerObj["score"].toInt();
        game->setPlayerScore(score, colour);
    }
}

void FileIO::jsonToBoard(QJsonObject boardObject, Game* gamemodel){
    if (!boardObject.contains("board")) {
        qDebug() << "'board' key not found in boardObject";
        return;
    } else if (!boardObject["board"].isArray()){
        qDebug() << "'board' is not an array in JSON.";
    }

    QJsonArray boardArray = boardObject["board"].toArray();
    Board& board = gamemodel->getBoard();

    board.clear();
    for(int x=0; x<Board::getSize(); x++){
        QJsonArray rij = boardArray[x].toArray();
        for(int y=0; y<Board::getSize(); y++){
            QJsonObject pieceObj = rij[y].toObject();
            if (!pieceObj.isEmpty()) {
                BadPieceClass piece = FileIO::jsonToPiece(pieceObj, gamemodel);
                board.putPieceAt(QPoint{x, y}, piece);
            }
        }
    }
}

void FileIO::loadBoard(Game* game, QString filePath){
    QFile file = QFile(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading:" << file.errorString();
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject rootObj = doc.object();

    if (!rootObj.contains("board")) {
        qDebug() << "'board' key not found in JSON.";
        return;
    }
    FileIO::jsonToBoard(rootObj, game);

    if (!rootObj.contains("players")) {
        qDebug() << "'players' key not found in JSON.";
        return;
    }
    FileIO::jsonToPlayers(game, rootObj);
}

// ==========================
// == Saving functionality ==
// ==========================

QJsonObject FileIO::pieceToJson(const BadPieceClass* piece){
    QJsonObject jsonObject;
    if (piece != nullptr){
        jsonObject["type"] = BadPieceClass::getTypeName(piece->getType());
        jsonObject["player_colour"] = Player::getColourName(piece->getPlayer().getColor());

        QJsonObject dirobj;
        dirobj["x"] = piece->getWalkPattern().forwardDirection.x();
        dirobj["y"] = piece->getWalkPattern().forwardDirection.y();
        jsonObject["direction"] = dirobj;
    }
    return jsonObject;
}

QJsonObject FileIO::playerToJson(const std::shared_ptr<Player>* player){
    QJsonObject jsonObject;
    if (player != nullptr){
        jsonObject["naam"] = player->get()->getName();
        jsonObject["colour"] = Player::getColourName(player->get()->getColor());
        jsonObject["score"] = player->get()->getScore();
    }
    return jsonObject;
}

QJsonObject FileIO::playersToJson(const std::shared_ptr<Player>* players, Player curr){
    QJsonObject jsonObject;
    QJsonArray playersJson;

    for (int i = 0; i<Game::getNumberOfPlayer(); i++){
        playersJson.append(playerToJson(&players[i]));
    }
    jsonObject["allPlayers"] = playersJson;
    jsonObject["currentPlayer"] = Player::getColourName(curr.getColor());

    return jsonObject;
}

QJsonObject FileIO::boardToJson(const Board* board){
    QJsonObject boardObject;
    QJsonArray boardArray;
    for(int x=0; x<Board::getSize(); x++){
        QJsonArray row;
        for(int y=0; y<Board::getSize(); y++){
            BadPieceClass* piece = board->getPieceAt(QPoint(x, y));

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

int FileIO::save(Game* game, QString filePath){
    QFile file = QFile(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return EXIT_FAILURE;
    }

    QJsonObject rootJsonObject;
    rootJsonObject["board"] = boardToJson(&(game->getBoard()))["board"];
    rootJsonObject["players"] = playersToJson(game->getPlayers().data(), game->getCurrentPlayer());
    QJsonDocument jsonDocument(rootJsonObject);

    file.write(jsonDocument.toJson());
    file.close();

    qDebug() << "File written successfully.";
    return 0; // Exit successfully
}