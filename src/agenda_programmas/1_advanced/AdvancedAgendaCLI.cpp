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
    cin >> name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter description of new Event: ";
    getline(cin, description);

    while (!isDateTimeInput(input)) {
        cout << "Enter date and time: ";
        getline(cin, input);
        dt = DateTime::parseDateTime(input);
    }

    cout << "Enter duration in minutes: ";
    cin >> duration;

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
    cin >> oldName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << agenda->getEvents(oldName) << endl;

    cout << "Enter new name: ";
    cin >> newName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (!isDateTimeInput(input)) {
        cout << "Enter new date and time: ";
        getline(cin, input);
        dt = DateTime::parseDateTime(input);
    }

    cout << "Enter new duration: ";
    cin >> duration;

    cout << "Enter new attendees (comma-separated): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    attendees = getAttendees(input);
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

void AdvancedAgendaCLI::printEvents(std::string name) const {
    cout << agenda->getEvents(name) << endl;
}

AdvancedAgendaCLI::AdvancedAgendaCLI(AdvancedAgenda *agenda)
        : agenda(agenda) {
}