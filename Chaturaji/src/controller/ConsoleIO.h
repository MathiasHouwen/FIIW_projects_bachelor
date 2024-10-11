

#ifndef CHATURAJI_CONSOLEIO_H
#define CHATURAJI_CONSOLEIO_H

#include <iostream>

class ConsoleIO {
public:
    ConsoleIO();
    QPoint getCords();
    bool exit();
    QString getPlayerName();
private:
    bool m_exit;
};


#endif //CHATURAJI_CONSOLEIO_H
