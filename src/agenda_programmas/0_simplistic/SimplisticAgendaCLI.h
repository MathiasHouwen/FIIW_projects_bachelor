//
// Volledig gemaakt door Mathias
//

#ifndef SYMPLISTICCONSOLEIO_H
#define SYMPLISTICCONSOLEIO_H


#include <set>
#include "../../event_classes/Event.h"
#include "SimplisticAgenda.h"
#include "../../util/CLIInterface.h"


class SimplisticAgendaCLI:CLIInterface {
private:
    SimplisticAgenda *agenda;
    void printUserAganda(std::string);
    void printDateTime(DateTime);
    static bool isDateTimeInput(const string &input);

public:
    explicit SimplisticAgendaCLI(SimplisticAgenda *agenda);

    using EventSet = std::set<Event, Event::eventComparator>;
    void getInput() override;

};



#endif //SYMPLISTICCONSOLEIO_H
