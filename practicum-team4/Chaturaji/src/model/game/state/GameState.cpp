// taakverdeling: zie h-file


#include "GameState.h"
#include "../bots/Bot.h"

Board &GameState::getBoard() {
    return board;
}

bool GameState::isGameOver() const {
    return gameOver;
}

Color GameState::getCurrentTurn() const {
    Color colors[4] = {Color::BLUE, Color::RED, Color::YELLOW, Color::GREEN};
    return colors[turn];
}

void GameState::advance() {
    move++;
    if(move == 2){
        dice.doubleDobbel();
        move = 0;
        int attempts = 0;
        do{
            turn++;
            if(turn == 4) turn = 0;
            attempts++;
            if(attempts >= 3){
                gameOver = true;
                break;
            }
        } while(players[getCurrentTurn()] && !players[getCurrentTurn()]->isAlive());
    }
}

Player* GameState::getCurrentPlayer() {
    return players[getCurrentTurn()];
}

Dice &GameState::getDice() {
    return dice;
}

int GameState::getCurrentMove() const {
    return move;
}

Player* GameState::getPlayerByColor(Color color) {
    return players[color];
}

void GameState::clearPlayers() {
    for(auto player : players){
        delete player;
    }
    players.clear();
}

void GameState::addPlayer(Player player) {
    Player* playerRef = new Player(player);
    players[player.getColor()] = playerRef;
}

void GameState::addPlayer(QString name) {
    if(name.isEmpty()) name = "new player";
    auto colAndSide = getAvialableColorAndSide();
    Player* player = new Player(colAndSide.first, name, colAndSide.second);
    players[colAndSide.first] = player;
}

void GameState::addBot(QString name, std::shared_ptr<MoveStrategy> strategy) {
    if(name.isEmpty()) name = "new bot";
    auto colAndSide = getAvialableColorAndSide();
    Player* player = new Bot(colAndSide.first, name, colAndSide.second, strategy);
    players[colAndSide.first] = player;
}

QPair<Color, HomeBoardSide> GameState::getAvialableColorAndSide() {
    Color colors[4] = {Color::BLUE, Color::RED, Color::YELLOW, Color::GREEN};
    HomeBoardSide sides[4] = {HomeBoardSide::LEFT, HomeBoardSide::BOTTOM, HomeBoardSide::TOP, HomeBoardSide::RIGHT};
    int i = -1;
    for(auto color : colors) {
        i++;
        if (players.contains(color)) continue;
        return {color, sides[i]};
    }
    return {Color::NONE, HomeBoardSide::BOTTOM};
}
