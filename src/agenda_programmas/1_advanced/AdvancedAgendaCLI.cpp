//
// Created by robin on 17/10/2024.
//

#include "AdvancedAgendaCLI.h"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

void AdvancedAgendaCLI::addEvent() const {
    std::string name;
    std::string description;
    string input;
    DateTime dt = DateTime(0, 0, 0, 0, 0);
    int duration;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter description of new Event: ";
    getline(cin, description);

    while (!isDateTimeInput(input)) {
        cout << "Enter date and time: ";
        getline(cin, input);
    }
    dt = DateTime::parseDateTime(input);

    cout << "Enter duration in minutes: ";
    cin >> duration;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    TimeSpan timeSpan = TimeSpan(dt, duration);
    Event event = Event(timeSpan, description);
    cout << endl << event.toString() << endl;
    agenda->insertHash(name, description, dt, event);
}

bool AdvancedAgendaCLI::isDateTimeInput(const std::string &input) {
    // Check if input contains both '-' and ':'
    return input.find('-') != std::string::npos && input.find(':') != std::string::npos;
}

void AdvancedAgendaCLI::updateEvent() const {
    std::string oldName;
    std::string newName;
    int duration;
    DateTime dt = DateTime(0, 0, 0, 0, 0);
    string input;
    std::vector<std::string> attendees;

    cout << "Enter name of event: ";
    getline(cin, oldName);

    cout << agenda->getEvents(oldName)->begin()->getDescription() << endl;

    cout << "Enter new name: ";
    getline(cin, newName);

    while (!isDateTimeInput(input)) {
        cout << "Enter new date and time: ";
        getline(cin, input);
        dt = DateTime::parseDateTime(input);
    }

    cout << "Enter new duration: ";
    cin >> duration;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new attendees (comma-separated): ";
    getline(cin, input);
    attendees = getAttendees(input);
    Event event = Event(TimeSpan(dt, duration), newName);
    agenda->linkAttendees(attendees, event);
    agenda->updateEvent(oldName, newName, dt, duration, attendees);
}

std::vector<std::string> AdvancedAgendaCLI::getAttendees(std::string input) {
    std::vector<std::string> attendees;
    std::stringstream ss(input);
    std::string attendee;

    while (getline(ss, attendee, ',')) {
        attendees.push_back(attendee);
    }

    return attendees;
}

void AdvancedAgendaCLI::askUser() {
    cout << "give name: ";
    string name;
    getline(cin, name);
    printEvents(name);
}

void AdvancedAgendaCLI::printEvents(const std::string& name) const {
    const EventSet *events = agenda->getEvents(name);

    if (events == nullptr || events->empty()) {
        cout << "No events found for user: " << name << endl;
        return;
    }

    for(auto itr : *events){
        cout << itr.toString() << endl;
    }
}

AdvancedAgendaCLI::AdvancedAgendaCLI(AdvancedAgenda *agenda)
        : agenda(agenda) {
}

void AdvancedAgendaCLI::getInput() {
    char action;
    cout << "Actions: 'A':add event, 'U':update event, 'P':print all events of user"<<endl;
    cout << "Select an option by its letter ";
    cin >> action;
    if(action=='A'){
        addEvent();
    } else if(action=='U'){
        updateEvent();
    } else if(action=='P'){
        askUser();
    }
}
