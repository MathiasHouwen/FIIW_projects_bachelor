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
        cout << itr.getAttendees()[0] + " "
            + itr.getDescription() + " "
            + to_string(itr.getTimeSpan().getDuration()) << endl;
    }
}

bool SimplisticAgendaCLI::isDateTimeInput(const std::string &input) {
    // Check if input contains both '-' and ':'
    return input.find('-') != std::string::npos && input.find(':') != std::string::npos;
}

void SimplisticAgendaCLI::getInput() {
    string input;
    cout << "Enter name or date and time";
    getline(cin, input);

    if(isDateTimeInput(input)){
        DateTime dt = DateTime::parseDateTime(input);
        printDateTime(dt);
        return;
    }
    printUserAganda(input);
}

SimplisticAgendaCLI::SimplisticAgendaCLI(const SimplisticAgenda &agenda) : agenda(agenda) {}