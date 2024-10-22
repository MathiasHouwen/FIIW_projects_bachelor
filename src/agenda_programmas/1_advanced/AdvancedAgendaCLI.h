//
// Created by robin on 17/10/2024.
//

#ifndef ADVANCEDCONSOLEIO_H
#define ADVANCEDCONSOLEIO_H
#include "AdvancedAgenda.h"
#include "../../util/CLIInterface.h"


class AdvancedAgendaCLI:CLIInterface {
    private:
    AdvancedAgenda *agenda;
    static bool isDateTimeInput(const std::string &input);
    static std::vector<std::string> getAttendees(std::string input);
    void printEvents(const std::string &name) const;

    public:
    explicit AdvancedAgendaCLI(AdvancedAgenda *agenda);
    using EventSet = std::set<Event, Event::eventComparator>;

    void addEvent() const;
    void updateEvent() const;
    void askUser();

    void getInput() override;

};



#endif //ADVANCEDCONSOLEIO_H
