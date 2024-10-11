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

GameView::GameView(Game &game) : model{game} {}
