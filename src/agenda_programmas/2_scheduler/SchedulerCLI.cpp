//
// Volledig gemaakt door Ebbe
//


#include "SchedulerCLI.h"
#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// (Aan de CLI classes is geen aandacht besteed. kwaliteit is hier dus wel veel minder)

void SchedulerCLI::getInput() {
    char action;
    cout << "Actions: 'P':plan event, 'S':print all sorted events"<<endl;
    cout << "Select an option by its letter ";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(action=='P'){
        plan();
    } else if(action=='S'){
        print();
    }
}

SchedulerCLI::SchedulerCLI(Scheduler* scheduler) : scheduler(scheduler) {}

void SchedulerCLI::plan() {
    std::string description;
    string input;
    DateTime dt = DateTime(0, 0, 0, 0, 0);
    int duration;

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

    std::vector<std::string> attendees;
    std::string attendeeInput;

    while (true) {
        std::cout << "Enter an attendee (enter '-' to stop adding attendees): ";
        std::getline(std::cin, attendeeInput);
        if (attendeeInput == "-") {
            break;
        }
        attendees.push_back(attendeeInput);
    }
    cout << "chosen attendees:"<<endl;
    for(const string& att : attendees){
        cout<<" - "<<att<<endl;
    }
    scheduler->plan(attendees,event);
}

void SchedulerCLI::print() {
    std::vector<std::string> users;
    std::string userInput;

    while (true) {
        std::cout << "Enter a user (enter '-' to stop adding users): ";
        std::getline(std::cin, userInput);
        if (userInput == "-") {
            break;
        }
        users.push_back(userInput);
    }
    cout << "chosen users:"<<endl;
    for(const string& att : users){
        cout<<" - "<<att<<endl;
    }
    list<Event> events = scheduler->getSortedAgenda(users);
    for(Event e : events){
        cout<<" - "<<e.toString()<<endl;
    }
}

bool SchedulerCLI::isDateTimeInput(const string &input) {
    // Check if input contains both '-' and ':'
    return input.find('-') != std::string::npos && input.find(':') != std::string::npos;
}

