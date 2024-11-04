//
// Volledig gemaakt door Robin
//

#include "AdvancedAgenda.h"

#include <iostream>
#include <ostream>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// 2 maps -> map 1 user name > list of event pointers
// map 2 datetime -> list<event*>
// Event = naam & timespan

// TODO: MAAK LIJST -> op volgorde inserten
// DOORMIDDEL SET

// add event to hashmap with respective key
void AdvancedAgenda::insertHash(const std::string& personName, const std::string& eventName, DateTime dateTime, Event event) {
    EventSet *setEventName = m_eventNameHash[eventName];
    if (!setEventName) {
        setEventName = new EventSet();
        m_eventNameHash[eventName] = setEventName;
    }
    setEventName->insert(event);
    EventSet *setPersonName = m_personNameHash[personName];
    if (!setPersonName) {
        setPersonName = new EventSet();
        m_personNameHash[personName] = setPersonName;
    }
    setPersonName->insert(event);
    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    if (!setDateTime) {
        setDateTime = new EventSet();
        m_dateTimeHash[dateTime.toString()] = setDateTime;
    }
    setDateTime->insert(event);
}

void AdvancedAgenda::eraseHash(Event event, std::string personName) {
    m_dateTimeHash[event.getTimeSpan().getStartTime().toString()]->erase(event);
    m_eventNameHash[event.getDescription()]->erase(event);
    m_personNameHash[personName]->erase(event);
}

// get event from hashmap with respective name (person name or event name)
AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(const string &name) {
    AdvancedAgenda::EventSet *eventSet = m_eventNameHash[name];
    if (eventSet == nullptr || eventSet->empty()) {
        eventSet = m_personNameHash[name];
    }
    return eventSet;
}

// get event from hashmap with respective dateTime
AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}

// filters attendees on who is free
void AdvancedAgenda::setFilteredAttendees(Event& event, const std::vector<std::string>& attendees) {
    std::vector<std::string> result;
    for(const std::string& attendee : attendees) {
        EventSet* events = getEvents(attendee);
        if(!checkOverlap(*events, event)) {
            result.push_back(attendee);
        }
    }
    event.set_attendees(result);
}

bool AdvancedAgenda::checkOverlap(const EventSet &events, const Event& event) {
    auto higher = events.lower_bound(event);
    if (higher != events.end() && compareTimes(higher->getTimeSpan(), event.getTimeSpan())) {
        return true;
    }
    if (higher != events.begin()) {
        auto lower = std::prev(higher);
        if(compareTimes(lower->getTimeSpan(), event.getTimeSpan())) return true;
    }
    return false;
}

void AdvancedAgenda::loadFromFile(string filePath) {
    FileInputReader file(filePath);
    while(file.hasNext()){
        FileInputReader::Entry line = file.nextLine();
        Event event = line.event;
        insertHash(line.username, event.getDescription(), line.event.getTimeSpan().getStartTime(), line.event);
    }
}


// returns true if time 1 is before or same as time 2
bool AdvancedAgenda::compareTimes(const TimeSpan &time1, const TimeSpan &time2) {
    DateTime thisStart = time1.getStartTime();
    DateTime thisEnd = time1.getEndTime();
    DateTime otherStart = time2.getStartTime();
    DateTime otherEnd = time2.getEndTime();

    return (thisStart < otherEnd) && (otherStart < thisEnd);
}

void AdvancedAgenda::updateEvent(const std::string& eventName, const std::string& newName, const DateTime &dateTime, const int duration, std::vector<std::string> &attendees) {
    string personName;
    cout << "Enter your name: " << endl;
    getline(cin, personName);
    if(getEvents(eventName)->empty()) {
        cout << "Event " << eventName << " does not exist" << endl;
        return;
    }
    const TimeSpan timespan = TimeSpan(dateTime, duration);
    Event newEvent = Event(timespan, newName);
    Event oldEvent = Event(getEvents(eventName)->begin().operator*().getTimeSpan(), getEvents(eventName)->begin().operator*().getDescription());
    std::vector<std::string> oldattendees = oldEvent.getAttendees();
    removeAttendees(oldattendees, oldEvent);
    eraseHash(oldEvent, personName);
    insertHash(personName, newName, dateTime, newEvent);
}

void AdvancedAgenda::printEvents(const std::string& personName) {
    EventSet* events = getEvents(personName);
    cout << "Events: " << endl;
    for(Event event : *events) {
        cout << event.toString() << endl;
    }
}

void AdvancedAgenda::linkAttendees(std::vector<std::string> &attendees, Event event) {
    for(const std::string& attendee : attendees) {
        EventSet *setPersonName = m_personNameHash[attendee];
        if (!setPersonName) {
            setPersonName = new EventSet();
            m_personNameHash[attendee] = setPersonName;
        }
        setPersonName->insert(event);
    }
}

void AdvancedAgenda::removeAttendees(std::vector<std::string> &attendees, Event event) {
    for(const std::string& attendee : attendees) {
        m_personNameHash[attendee]->erase(event);
    }
}