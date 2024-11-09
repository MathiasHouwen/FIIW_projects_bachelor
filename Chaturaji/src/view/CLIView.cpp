#include "CLIView.h"

#include <iostream>
#include <ostream>

// gemaakt door robin
// kleuren en markeringen door ebbe

using namespace std;

void CLIView::printBoard() const {
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
string CLIView::getCellString(QPoint cell) const {
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
        if(!selection && piece->getPlayer() == model.getCurrentPlayer()
            && (piece->getType() == model.getDice().first
            || piece->getType() == model.getDice().second)){
            background = 45;
        }
        symb = getPieceSymbol(*piece);
        color = asciiEscColorCode(piece->getPlayer().getColour());
    }
    return asciiEscString(color, background, symb);
}

CLIView::CLIView(Game &game) : model{game} {
    system("cls");
}

int CLIView::asciiEscColorCode(Player::colour color) {
    switch (color) {
        case Player::colour::RED: return 31;
        case Player::colour::GREEN: return 32;
        case Player::colour::YELLOW: return 33;
        case Player::colour::BLUE: return 34;
    }
}

std::string CLIView::asciiEscString(int color, int background, const std::string& str) {
    string asciiEscString = "\033[" + std::to_string(color);
    if(background != -1)
        asciiEscString += ";" + std::to_string(background);

    asciiEscString += "m" + str + "\033[0m";
    return asciiEscString;
}

std::string CLIView::getPieceSymbol(Piece piece) {
    switch (piece.getType()) {
        case Piece::Type::PAWN: return "PWN";
        case Piece::Type::BOAT: return "BT_";
        case Piece::Type::KING: return "KNG";
        case Piece::Type::KNIGHT: return "HRS";
        case Piece::Type::ELEPH: return "ELE";
    }
}
void CLIView::printDice() const {
    QPair<Piece::Type, Piece::Type> dice = model.getDice();
    cout << "The dice gave you the choises: [ ";
    cout << Piece::getTypeName(dice.first).toStdString() << ", ";
    cout << Piece::getTypeName(dice.second).toStdString() << " ]" << endl;
}

void CLIView::printMove() {
    QPair<Piece::Type, Piece::Type> dice = model.getDice();
    int move = model.getMove();
    if(move == 0){
        cout << "Move 1/2. Pick one of the choises" << endl;
    } else {
        cout << "Move 2/2. Remaining choise: ";
        if(dice.first == Piece::Type::USED)
            cout << Piece::getTypeName(dice.second).toStdString() << endl;
        else
            cout << Piece::getTypeName(dice.first).toStdString() << endl;
    }
}

void CLIView::printTurn() {
    Player player = model.getCurrentPlayer();
    int color = asciiEscColorCode(player.getColour());
    cout << "Turn of player: ";
    cout << asciiEscString(color, 47, " "+player.getName().toStdString()+" ");
    cout << "  -  score: " << player.getScore();
    cout << endl;
}

void CLIView::update() {
    //system("CLS");
    //cout.flush();
    printBoard();
    printTurn();
    printDice();
    printMove();
}
