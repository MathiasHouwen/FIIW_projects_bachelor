

#include <QTextStream>
#include <QPoint>
#include <qstring.h>
#include "ConsoleIO.h"

using namespace std;

ConsoleIO::ConsoleIO() {
    m_exit = false;
}

QPoint ConsoleIO::askCoords() {
    string coord;
    askQuestion("Select a square.", "ex. A1");
    cin >> coord;
    m_exit = coord == "Q" || coord == "q";


    int col = min(abs(coord[0] - 'A'), abs(coord[0] - 'a'));
    int row = 8 -(coord[1] - '0');

    return QPoint{col, row};
}

bool ConsoleIO::exit() {
    return m_exit;
}

QString ConsoleIO::getPlayerName(int playerID) {
    QString name;
    QTextStream in(stdin);
    askQuestion("What is player" + to_string(playerID) + "'s name?", "name");
    in >> name;
    m_exit = name == "Q" || name == "q";
    return name;
}

bool ConsoleIO::askMoveConfirmation() {
    askQuestion("Do you want to take this move or skip it?", "'t'/'s'");
    QTextStream in(stdin);
    QChar choice;
    in >> choice;
    m_exit = choice == 'Q' || choice == 'q';
    return choice == 't';
}

void ConsoleIO::askQuestion(std::string question, std::string options) {
    cout << "\033[36m  -> ";
    cout << question;
    cout << "\033[0m [" << options << "]: ";
}
