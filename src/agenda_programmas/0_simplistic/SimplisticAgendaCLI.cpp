//
// Created by robin on 16/10/2024.
//

#include "SimplisticAgendaCLI.h"

#include <iostream>
#include "string"
#include "SimplisticAgenda.h"

void SimplisticAgendaCLI::printUserAganda(std::string name) {
    EventSet *events = agenda.getEvents(name);

    for(auto itr : *events){
        cout << itr.toString() << endl;
    }
}

void SimplisticAgendaCLI::printDateTime(DateTime dateTime) {
    EventSet *events = agenda.getEvents(dateTime);

    for(auto itr : *events){
        cout << itr.toString() << endl;
    }
}

void SimplisticAgendaCLI::getInput() {

}

SimplisticAgendaCLI::SimplisticAgendaCLI(const SimplisticAgenda &agenda) : agenda(agenda) {}
