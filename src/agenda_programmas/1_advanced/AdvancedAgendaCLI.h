//
// Created by robin on 17/10/2024.
//

#ifndef ADVANCEDCONSOLEIO_H
#define ADVANCEDCONSOLEIO_H
#include "AdvancedAgenda.h"


class AdvancedAgendaCLI {
    private:
    AdvancedAgenda *agenda;

    public:
    explicit AdvancedAgendaCLI(AdvancedAgenda *agenda);
    using EventSet = std::set<Event, Event::eventComparator>;
    void addEvent() const;
    static bool isDateTimeInput(const std::string &input);
    void updateEvent() const;
    static std::vector<std::string> getAttendees(std::string input);
    void askUser();
    void printEvents(const std::string &name) const;
};



#endif //ADVANCEDCONSOLEIO_H
