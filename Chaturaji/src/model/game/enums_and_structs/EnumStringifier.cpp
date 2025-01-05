//
// Created by ebbew on 5-1-2025.
//

#include "EnumStringifier.h"

QString EnumStringifier::cToString(Color color) {
    switch (color) {
        case Color::YELLOW: return "yellow";
        case Color::RED: return "red";
        case Color::BLUE: return "blue";
        case Color::GREEN: return "green";
        case Color::NONE: return "grey";
    }
}

QString EnumStringifier::sToString(HomeBoardSide side) {
    switch (side) {
        case HomeBoardSide::LEFT: return "left";
        case HomeBoardSide::RIGHT: return "right";
        case HomeBoardSide::TOP: return "top";
        case HomeBoardSide::BOTTOM: return "bottom";
    }
}

QString EnumStringifier::tToString(PieceType type) {
    switch (type) {
        case PieceType::PAWN: return "pawn";
        case PieceType::KING: return "king";
        case PieceType::ELEPHANT: return "elephant";
        case PieceType::HORSE: return "horse";
        case PieceType::BOAT: return "boat";
    }
}

Color EnumStringifier::cFromString(QString color) {
    if(color == "red") return Color::RED;
    if(color == "blue") return Color::BLUE;
    if(color == "yellow") return Color::YELLOW;
    if(color == "green") return Color::GREEN;
    if(color == "grey") return Color::NONE;
}

HomeBoardSide EnumStringifier::sFromString(QString side) {
    if(side == "left") return HomeBoardSide::LEFT;
    if(side == "right") return HomeBoardSide::RIGHT;
    if(side == "top") return HomeBoardSide::TOP;
    if(side == "bottom") return HomeBoardSide::BOTTOM;
}

PieceType EnumStringifier::tFromString(QString type) {
    if(type == "pawn") return PieceType::PAWN;
    if(type == "king") return PieceType::KING;
    if(type == "elephant") return PieceType::ELEPHANT;
    if(type == "horse") return PieceType::HORSE;
    if(type == "boat") return PieceType::BOAT;
}
