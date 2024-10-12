

#ifndef CHATURAJI_CONSOLEIO_H
#define CHATURAJI_CONSOLEIO_H

#include <iostream>

class ConsoleIO {
public:
    ConsoleIO();
    QPoint getCords();
    bool exit();
    QString getPlayerName(int playerID);
    bool askMoveConfirmation();
    bool askReplay();
private:
    bool m_exit;
    void askQuestion(std::string question, std::string options);
};


#endif //CHATURAJI_CONSOLEIO_H
