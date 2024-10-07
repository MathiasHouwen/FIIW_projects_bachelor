

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

    int x = cord[0] - 'A';
    // cout << "x: " << x;
    int y = cord[1] - '0' - 1;
    // cout << "y: " << y;

    return QPoint{x, y};
}

bool ConsoleIO::exit() {
    return m_exit;
}
