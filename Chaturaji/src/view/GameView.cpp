#include "GameView.h"

#include <iostream>
#include <ostream>


using namespace std;

void GameView::printBoard() const {
    Board gameBoard = model.getBoard();
    const int boardSize = gameBoard.getSize();
    const int cellWidth = 3;
    const int cellPad = 1;

    // TOP INDICATORS
    cout << "     ";
    for(int i=0;i<8;i++) {
        char letter = 'A'+i;
        cout << string(cellPad+1, ' ') << "[" << letter << "]" << string(cellPad, ' ');
    }
    cout << endl;

    cout << "     " << string(1+boardSize*(cellWidth+2*cellPad+1), '-') << endl;

    for(int row = 0; row < boardSize; row++) {
        cout << "[" << 8-row << "]  |";
        for(int col = 0; col < boardSize; col++) {

            string cellString = getCellString({col, row});
            cout << string(cellPad, ' ') << cellString << string(cellPad, ' ') << "|";
        }
        cout << endl;
        cout << "     " << string(1+boardSize*(cellWidth+2*cellPad+1), '-') << endl;
    }
}
string GameView::getCellString(QPoint cell) const {
    int color = 0; // default
    string symb = " . ";
    int background = -1;
    QPoint* selection = model.getCurrentlySelectedCell();
    if(selection && *selection == cell)
        background = 47;
    else if(selection && model.getPossibleMoves().contains(cell))
        background = 45;

    Piece* piece = model.getBoard().getCell(cell);
    if(piece){
        symb = getPieceSymbol(*piece);
        color = asciiEscColorCode(piece->getPlayer().getMColour());
    }
    return asciiEscString(color, background, symb);
}

GameView::GameView(Game &game) : model{game} {
    system("cls");
}

int GameView::asciiEscColorCode(Player::colour color) {
    switch (color) {
        case Player::colour::RED: return 31;
        case Player::colour::GREEN: return 32;
        case Player::colour::YELLOW: return 33;
        case Player::colour::BLUE: return 34;
    }
}

std::string GameView::asciiEscString(int color, int background, const std::string& str) {
    string asciiEscString = "\033[" + std::to_string(color);
    if(background != -1)
        asciiEscString += ";" + std::to_string(background);

    asciiEscString += "m" + str + "\033[0m";
    return asciiEscString;
}

std::string GameView::getPieceSymbol(Piece piece) {
    switch (piece.getType()) {
        case Piece::Type::PAWN: return "PWN";
        case Piece::Type::BOAT: return "BT_";
        case Piece::Type::KING: return "KNG";
        case Piece::Type::KNIGHT: return "HRS";
        case Piece::Type::ELEPH: return "ELE";
    }
}
void GameView::printTypes(Piece::Type type) const {
    cout << "move: ";
    switch(type) {
        case Piece::Type::PAWN: cout << "Pawn" << endl; break;
        case Piece::Type::KNIGHT: cout << "Knight" << endl; break;
        case Piece::Type::KING: cout << "King" << endl; break;
        case Piece::Type::BOAT: cout << "Boat" << endl; break;
        case Piece::Type::ELEPH: cout << "Elephant" << endl; break;
        default: cout << "Unknown" << endl; break;
    }
}
