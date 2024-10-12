

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
    cout << "Please enter the coordinate: ";
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
    cout << "Please enter the player " << playerID << " name: ";
    input >> name;
    return name;
}
