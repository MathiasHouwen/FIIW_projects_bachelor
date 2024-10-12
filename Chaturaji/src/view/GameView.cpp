#include "GameView.h"

#include <iostream>
#include <ostream>


using namespace std;

void GameView::printBoard() const {
    Board gameBoard = model.getBoard();
    cout << "     ";
    for(int i=0;i<8;i++) {
        char letter = 'A'+i;
        cout << "    [" << letter << "]";
    }

    cout << endl;

    for(int row = 0; row < gameBoard.getSize(); row++) {
        cout << "[" << 8-row << "]   |  ";
        for(int col = 0; col < gameBoard.getSize(); col++) {
            Piece* cell = gameBoard.getCell({col, row});
            std::string celSymbol = cell ? "[]" : "..";
            cout << celSymbol << "  |  ";
        }
        cout << endl;
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

GameView::GameView(Game &game) : model{game} {}
