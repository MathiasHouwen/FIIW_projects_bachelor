//
// Created by robin on 16/10/2024.
//

#include "Agenda.h"

#include <utility>

Agenda::Agenda(std::string name)
            : name(std::move(name)) {
}

std::vector<Events> Agenda::getEvents() {
    return events;
}

void Agenda::addEvent(Events event) {
    // TODO: hangt van datastructuur af
}

void Agenda::removeEvent(Events event) {
    // TODO: hangt van datastructuur af
}

std::string Agenda::getName() {
    return name;
}


