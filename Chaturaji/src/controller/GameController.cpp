//
// Created by ebbew on 5-1-2025.
//

#include "GameController.h"

QSet<ClassifiedMove> GameController::getMovesForHighlight() {
    if(state == StepState::READYTOPICK)
        return {};
    else{
        auto piece = game.getGameState().getBoard().getPieceAt(selectedCell.value());
        return movesManager.generateClassifiedMoves(piece.value(), selectedCell.value());
    }
}

GameController::GameController(Game& game) :
    game(game),
    movesManager(game.getGameState().getBoard()),
    querier(game.getGameState().getBoard()){}

void GameController::handleCellSelect(QPoint cell, PieceType pawnPromoteType) {
    if(state == StepState::READYTOPICK){
        if(game.isCellFromCurrentPlayer(cell)){
            selectedCell = cell;
            state = StepState::READYTOPLACE;
        }
    } else {
        game.doMove(selectedCell.value(), cell, pawnPromoteType);
        selectedCell = std::nullopt;
    }
}

bool GameController::moveIsPawnPromote(QPoint cell) {
    auto moves = getMovesForHighlight();
    for(auto move : moves){
        if(move.destination == cell){
            return move.specialMoveType == SpecialMoveType::PAWNPROMOTE;
        }
    }
    return false;
}

GameController::StepState GameController::getState() const {
    return state;
}

const std::optional<QPoint> &GameController::getSelectedCell() const {
    return selectedCell;
}

QSet<QPoint> GameController::getSelectablesForHighlight() {
    if(state == StepState::READYTOPLACE)
        return {};
    else{
        auto types = game.getGameState().getDice().getAllowedTypes();
        return querier.getPiecesWithTypesAndColor(types, game.getGameState().getCurrentTurn());
    }
}

Game &GameController::getGame() const {
    return game;
}


