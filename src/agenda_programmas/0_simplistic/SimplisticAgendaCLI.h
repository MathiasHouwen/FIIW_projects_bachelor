//
// Created by robin on 16/10/2024.
//

#ifndef SYMPLISTICCONSOLEIO_H
#define SYMPLISTICCONSOLEIO_H


#include <set>
#include "../../event_classes/Event.h"
#include "SimplisticAgenda.h"


class SimplisticAgendaCLI {
private:
    SimplisticAgenda agenda;
    void printUserAganda(std::string);
    void printDateTime(DateTime);
public:
    explicit SimplisticAgendaCLI(const SimplisticAgenda &agenda);

    using EventSet = std::set<Event, Event::eventComparator>;
    void getInput();
};



#endif //SYMPLISTICCONSOLEIO_H
