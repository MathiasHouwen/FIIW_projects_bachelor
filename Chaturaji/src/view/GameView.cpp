#include "GameView.h"

#include <iostream>
#include <ostream>

using namespace std;

void GameView::printBoard() {
    Board gameBoard = model.getBoard();
    gameBoard.setCell(4,5,true);
    const bool (*playBoard)[8] = gameBoard.getBoard();
    cout << "     ";
    for(int i=0;i<8;i++) {
        char letter = 'A'+i;
        cout << "   [" << letter << "]";
    }

    cout << endl;

    for(int i = 0; i < gameBoard.getWidth(); i++) {
        cout << "[" << 8-i << "]   |  ";
        for(int j = 0; j < gameBoard.getHeight(); j++) {
            cout << playBoard[i][j] << "  |  ";
        }
        cout << endl;
    }
}

GameView::GameView(Game &game) : model{game} {
    std::cout << "GameView model\t" << &model  << std::endl;
    std::cout << "GameView model->board\t" << &(model.getBoard())  << std::endl;
}
