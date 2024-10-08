#include "GameView.h"

#include <iostream>
#include <ostream>

using namespace std;

void GameView::printBoard() {
    Board gameBoard = model.getBoard();
    gameBoard.setCell(1,2,true);
    cout << "     ";
    for(int i=0;i<8;i++) {
        char letter = 'A'+i;
        cout << "    [" << letter << "]";
    }

    cout << endl;

    for(int row = 0; row < gameBoard.getHeight(); row++) {
        cout << "[" << 8-row << "]   |  ";
        for(int col = 0; col < gameBoard.getWidth(); col++) {
            bool cell = gameBoard.getCell(row, col);
            std::string celSymbol = cell ? "[]" : "..";
            cout << celSymbol << "  |  ";
        }
        cout << endl;
    }
}

GameView::GameView(Game &game) : model{game} {
    std::cout << "GameView model\t" << &model  << std::endl;
    std::cout << "GameView model->board\t" << &(model.getBoard())  << std::endl;
}
