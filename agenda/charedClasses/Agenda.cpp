//
// Created by robin on 16/10/2024.
//

#include "Agenda.h"

#include <utility>

Agenda::Agenda(std::string name)
            : name(std::move(name)) {
}

std::vector<Event> Agenda::getEvents() {
    return events;
}

void Agenda::addEvent(Event event) {
    // TODO: hangt van datastructuur af
}

void Agenda::removeEvent(Event event) {
    // TODO: hangt van datastructuur af
}

std::string Agenda::getName() {
    return name;
}


