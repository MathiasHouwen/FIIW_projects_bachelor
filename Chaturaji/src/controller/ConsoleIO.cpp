

#include <QTextStream>
#include <QPoint>
#include "ConsoleIO.h"

using namespace std;

ConsoleIO::ConsoleIO() {
    m_exit = false;
}

QPoint ConsoleIO::getCords() {
    string cord;
    cout << "Please enter the coordinate: ";
    cin >> cord;

    if(cord == "Q" || cord == "q"){
        m_exit = true;
        return QPoint{-1, -1};
    }

    int col = cord[0] - 'A';
    int row = 8 -(cord[1] - '0');

    return QPoint{col, row};
}

bool ConsoleIO::exit() {
    return m_exit;
}
