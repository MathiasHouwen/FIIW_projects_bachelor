#include "GameView.h"

#include <iostream>
#include <ostream>

using namespace std;

void GameView::printBoard() {
    board.setCell(4,5,true);
    const bool (*playBoard)[8] = board.getBoard();
    cout << "     ";
    for(int i=0;i<8;i++) {
        char letter = 'A'+i;
        cout << "   [" << letter << "]";
    }

    cout << endl;

    for(int i = 0; i < board.getWidth(); i++) {
        cout << "[" << 8-i << "]   |  ";
        for(int j = 0; j < board.getHeight(); j++) {
            cout << playBoard[i][j] << "  |  ";
        }
        cout << endl;
    }
}
