//
// Created by robin on 16/10/2024.
//

#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>

#include "Event.h"

class Agenda {
    private:
        std::string name;
        std::vector<Event> events; // TODO: andere datastructuur gebruiken
    public:
        explicit Agenda(std::string name);
        ~Agenda() = default;
        std::vector<Event> getEvents(); // TODO: hangt van datastructuur af
        void addEvent(Event event);
        void removeEvent(Event event);
        std::string getName();
};



#endif //AGENDA_H
