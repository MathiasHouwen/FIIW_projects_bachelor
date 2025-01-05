// volledig van mathias
// nog steeds volledig van mathias

#include "FileIO.h"
#include "../game/enums_and_structs/EnumStringifier.h"

#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


FileIO::FileIO()= default;

// ===========================
// == Loading functionality ==
// ===========================

Piece FileIO::jsonToPiece(const QJsonObject &jsonObject) {
    PieceType type = EnumStringifier::tFromString(jsonObject["type"].toString());
    Color color = EnumStringifier::cFromString(jsonObject["color"].toString());
    HomeBoardSide side = EnumStringifier::sFromString(jsonObject["homeside"].toString());
    return Piece(color, type, side);
}

void FileIO::jsonToPlayers(Game& game, QJsonObject rootObj){
    QJsonArray players = rootObj["players"].toArray();
    for(auto playerVal : players){
        QJsonObject playerObj = playerVal.toObject();
        Color color = EnumStringifier::cFromString(playerObj["color"].toString());
        QString name = playerObj["name"].toString();
        int score = playerObj["score"].toInt();
        bool alive = playerObj["alive"].toBool();
        HomeBoardSide side = EnumStringifier::sFromString(playerObj["home"].toString());
        auto player = Player(color, name, side, score);
        game.getGameState().addPlayer(player);
        if(!alive) game.getGameState().getPlayerByColor(color)->kill();
    }
}

void FileIO::jsonToBoard(QJsonObject rootObj, Board& board){
    QJsonArray boardArray = rootObj["board"].toArray();
    board.clear();
    for(auto square : boardArray){
        QJsonObject squareObj = square.toObject();
        QPoint point(squareObj["x"].toInt(), squareObj["y"].toInt());
        Piece piece = jsonToPiece(squareObj["piece"].toObject());
        board.putPieceAt(point, piece);
    }
}

void FileIO::load(Game& game, QString filePath){
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
    FileIO::jsonToBoard(rootObj, game.getGameState().getBoard());

    if (!rootObj.contains("players")) {
        qDebug() << "'players' key not found in JSON.";
        return;
    }
    Color currentPlayer = EnumStringifier::cFromString(rootObj["currentPlayer"].toString());
    while (game.getGameState().getCurrentTurn() != currentPlayer){
        game.getGameState().advance();
    }
    FileIO::jsonToPlayers(game, rootObj);
}

// ==========================
// == Saving functionality ==
// ==========================

QJsonObject FileIO::pieceToJson(Piece piece){
    QJsonObject jsonObject;
    jsonObject["type"] = EnumStringifier::tToString(piece.getType());
    jsonObject["homeside"] = EnumStringifier::sToString(piece.getHomeSide());
    jsonObject["color"] = EnumStringifier::cToString(piece.getColor());
    return jsonObject;
}

QJsonArray FileIO::boardToJson(Board &board) {
    QJsonArray boardArray;
    for(auto cell : board.iterableCells()){
        auto piece = board.getPieceAt(cell).value();
        QJsonObject pieceObject = pieceToJson(piece);
        QJsonObject squareObject;
        squareObject["x"] = cell.x();
        squareObject["y"] = cell.y();
        squareObject["piece"] = pieceObject;
        boardArray.append(squareObject);
    }
    return boardArray;
}

QJsonArray FileIO::playersToJson(Game &game) {
    QJsonArray playersArray;
    Color colors[4] = {Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW};
    for(auto color : colors){
        auto player = game.getGameState().getPlayerByColor(color);
        QJsonObject playerObject;
        playerObject["name"] = player->getName();
        playerObject["color"] = EnumStringifier::cToString(player->getColor());
        playerObject["score"] = player->getScore();
        playerObject["alive"] = player->isAlive();
        playerObject["home"] = EnumStringifier::sToString(player->getHomeBoardSide());
        playersArray.append(playerObject);
    }
    return playersArray;
}

int FileIO::save(Game& game, QString filePath){
    QFile file = QFile(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return EXIT_FAILURE;
    }

    QJsonObject rootJsonObject;
    rootJsonObject["board"] = boardToJson(game.getGameState().getBoard());
    rootJsonObject["players"] = playersToJson(game);
    rootJsonObject["currentPlayer"] = EnumStringifier::cToString(game.getGameState().getCurrentTurn());
    QJsonDocument jsonDocument(rootJsonObject);

    file.write(jsonDocument.toJson());
    file.close();

    qDebug() << "File written successfully.";
    return 0; // Exit successfully
}
