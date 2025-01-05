// volledig van mathias
// nog steeds volledig van mathias

#include "FileIO.h"

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

Piece FileIO::jsonToPiece(const QJsonObject &jsonObject) {
    QString typestr = jsonObject["type"].toString();
    PieceType type = pieceTypeFromString(typestr);
    QString colourstr = jsonObject["color"].toString();
    Color color = ColorFromString(colourstr);
    QString sidestr = jsonObject["homeside"].toString();
    HomeBoardSide side = homeBoardSideFromString(sidestr);
    return Piece(color, type, side);
}

void FileIO::jsonToPlayers(Game& game, QJsonObject rootObj){
    QJsonArray players = rootObj["players"].toArray();
    game.getGameState().clearPlayers();
    for(auto playerVal : players){
        QJsonObject playerObj = playerVal.toObject();
        Color color = ColorFromString(playerObj["color"].toString());
        QString name = playerObj["name"].toString();
        int score = playerObj["score"].toInt();
        game.getGameState().addPlayer(Player(color, name, score));
    }
}

void FileIO::jsonToBoard(QJsonObject rootObj, Board& board){
    QJsonArray boardArray = rootObj["board"].toArray();
    board.clear();
    for(auto square : boardArray){
        QJsonObject squareObj = square.toObject();
        QPoint point(squareObj["x"].toInt(), squareObj["x"].toInt());
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
    FileIO::jsonToPlayers(game, rootObj);
}

// ==========================
// == Saving functionality ==
// ==========================
//
//QJsonObject FileIO::pieceToJson(Piece piece){
//    QJsonObject jsonObject;
//    jsonObject["type"] = pieceTypeToString(piece.getType());
//    jsonObject["homeside"] = homeBoardSideToString(piece.getHomeSide());
//    jsonObject["color"] = ColorToString(piece.getColor());
//    return jsonObject;
//}
//
//QJsonObject FileIO::playerToJson(const std::shared_ptr<Player>* player){
//    QJsonObject jsonObject;
//    if (player != nullptr){
//        jsonObject["naam"] = player->get()->getName();
//        jsonObject["colour"] = Player::getColourName(player->get()->getColor());
//        jsonObject["score"] = player->get()->getScore();
//    }
//    return jsonObject;
//}
//
//QJsonObject FileIO::playersToJson(const std::shared_ptr<Player>* players, Player curr){
//    QJsonObject jsonObject;
//    QJsonArray playersJson;
//
//    for (int i = 0; i<Game::getNumberOfPlayer(); i++){
//        playersJson.append(playerToJson(&players[i]));
//    }
//    jsonObject["allPlayers"] = playersJson;
//    jsonObject["currentPlayer"] = Player::getColourName(curr.getColor());
//
//    return jsonObject;
//}
//
//QJsonObject FileIO::boardToJson(const Board* board){
//    QJsonObject boardObject;
//    QJsonArray boardArray;
//    for(int x=0; x<Board::getSize(); x++){
//        QJsonArray row;
//        for(int y=0; y<Board::getSize(); y++){
//            BadPieceClass* piece = board->getPieceAt(QPoint(x, y));
//
//            if (piece != nullptr){
//                row.append(pieceToJson(piece));
//            } else {
//                row.append(QJsonValue::Null);
//            }
//        }
//        boardArray.append(row);
//    }
//    boardObject["board"] = boardArray;
//    return boardObject;
//}
//
//int FileIO::save(Game* game, QString filePath){
//    QFile file = QFile(filePath);
//
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        qDebug() << "Could not open file for writing:" << file.errorString();
//        return EXIT_FAILURE;
//    }
//
//    QJsonObject rootJsonObject;
//    rootJsonObject["board"] = boardToJson(&(game->getBoard()))["board"];
//    rootJsonObject["players"] = playersToJson(game->getPlayers().data(), game->getCurrentPlayer());
//    QJsonDocument jsonDocument(rootJsonObject);
//
//    file.write(jsonDocument.toJson());
//    file.close();
//
//    qDebug() << "File written successfully.";
//    return 0; // Exit successfully
//}

QString FileIO::pieceTypeToString(PieceType type) {
    switch (type) {
        case PieceType::PAWN: return "pawn";
        case PieceType::KING: return "king";
        case PieceType::ELEPHANT: return "elephant";
        case PieceType::HORSE: return "horse";
        case PieceType::BOAT: return "boat";
    }
}

QString FileIO::ColorToString(Color color) {
    switch (color) {
        case Color::YELLOW: return "yellow";
        case Color::RED: return "red";
        case Color::BLUE: return "blue";
        case Color::GREEN: return "green";
    }
}

PieceType FileIO::pieceTypeFromString(QString type) {
    if(type == "pawn") return PieceType::PAWN;
    if(type == "king") return PieceType::KING;
    if(type == "elephant") return PieceType::ELEPHANT;
    if(type == "horse") return PieceType::HORSE;
    if(type == "boat") return PieceType::BOAT;
}

Color FileIO::ColorFromString(QString color) {
    if(color == "red") return Color::RED;
    if(color == "blue") return Color::BLUE;
    if(color == "yellow") return Color::YELLOW;
    if(color == "green") return Color::GREEN;
}

QString FileIO::homeBoardSideToString(HomeBoardSide side) {
    switch (side) {
        case HomeBoardSide::LEFT: return "left";
        case HomeBoardSide::RIGHT: return "right";
        case HomeBoardSide::TOP: return "top";
        case HomeBoardSide::BOTTOM: return "bottom";
    }
}

HomeBoardSide FileIO::homeBoardSideFromString(QString side) {
    if(side == "left") return HomeBoardSide::LEFT;
    if(side == "right") return HomeBoardSide::RIGHT;
    if(side == "top") return HomeBoardSide::TOP;
    if(side == "bottom") return HomeBoardSide::BOTTOM;
}
