

#include <QTextStream>
#include <QPoint>
#include <qstring.h>
#include "ConsoleIO.h"

using namespace std;

ConsoleIO::ConsoleIO() {
    m_exit = false;
}

QPoint ConsoleIO::getCords() {
    string in;
    askQuestion("Select a square.", "ex. A1");
    cin >> in;

    if(in == "Q" || in == "q"){
        m_exit = true;
    }

    int col = min(abs(in[0] - 'A'), abs(in[0] - 'a'));
    int row = 8 -(in[1] - '0');

    return QPoint{col, row};
}

bool ConsoleIO::exit() {
    return m_exit;
}

QString ConsoleIO::getPlayerName(int playerID) {
    QString name;
    QTextStream input(stdin);
    askQuestion("What is player" + to_string(playerID) + "'s name?", "name");
    input >> name;
    return name;
}

bool ConsoleIO::askMoveConfirmation() {
    askQuestion("Do you want to take this move or skip it?", "'t'/'s'");
    QTextStream input(stdin);
    QChar choice;
    input >> choice;
    return choice == 't';
}

bool ConsoleIO::askReplay() {
    askQuestion("Do you want to replay?", "'y'/'n'");
    QTextStream input(stdin);
    QChar choice;
    input >> choice;
    return choice == 'y';
}

void ConsoleIO::askQuestion(std::string question, std::string options) {
    cout << "\033[36m  -> ";
    cout << question;
    cout << "\033[0m [" << options << "]: ";
}
