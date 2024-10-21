//
// Created by robin on 17/10/2024.
//

#ifndef ADVANCEDCONSOLEIO_H
#define ADVANCEDCONSOLEIO_H
#include "AdvancedAgenda.h"


class AdvancedAgendaCLI {
    private:
    AdvancedAgenda agenda;

    public:
    explicit AdvancedAgendaCLI(const AdvancedAgenda &agenda);
    using EventSet = std::set<Event, Event::eventComparator>;
    void addEvent();
    static bool isDateTimeInput(const std::string &input);
    void updateEvent();
    static std::vector<std::string> getAttendees(std::string input);
    void printEvents(std::string name);
};



#endif //ADVANCEDCONSOLEIO_H
