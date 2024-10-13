

#ifndef CHATURAJI_CONSOLEIO_H
#define CHATURAJI_CONSOLEIO_H

#include <iostream>

class ConsoleIO {
public:
    ConsoleIO();

    QPoint askCoords(); // vraagt voor de coordinaten van een cell
    bool exit();    // zegt of de user wil stoppen omdat 'Q' is ingegeven als antwoord
    QString getPlayerName(int playerID); // vraagt speler naam
    bool askMoveConfirmation(); // vraagt om verder te gaan met een move
private:
    bool m_exit;
    void askQuestion(std::string question, std::string options);    // steekt de vraag in mooi formaat en kleur
};


#endif //CHATURAJI_CONSOLEIO_H
