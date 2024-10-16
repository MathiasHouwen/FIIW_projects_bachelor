//
// Created by robin on 16/10/2024.
//

#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>

#include "Events.h"

class Agenda {
    private:
        std::string name;
        std::vector<Events> events; // TODO: andere datastructuur gebruiken
    public:
        explicit Agenda(std::string name);
        ~Agenda() = default;
        std::vector<Events> getEvents(); // TODO: hangt van datastructuur af
        void addEvent(Events event);
        void removeEvent(Events event);
        std::string getName();
};



#endif //AGENDA_H
