//
// Created by robin on 16/10/2024.
//

#include "AdvancedAgenda.h"

#include <iostream>
#include <ostream>
// 2 maps -> map 1 user name > list of event pointers
// map 2 datetime -> list<event*>
// Event = naam & timespan

// TODO: MAAK LIJST -> op volgorde inserten
// DOORMIDDEL SET

// add event to hashmap with respective key
void AdvancedAgenda::insertHash(const std::string& personName, const std::string& eventName, DateTime dateTime, Event* event) {
    EventSet *setEventName = m_eventNameHash[eventName];
    setEventName->insert(event);
    EventSet *setPersonName = m_personNameHash[personName];
    setPersonName->insert(event);
    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    setDateTime->insert(event);
}

// get event from hashmap with respective name (person name or event name)
AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(const string &name) {
    AdvancedAgenda::EventSet *eventSet = m_eventNameHash[name];
    if (eventSet->empty()) {
        return m_personNameHash[name];
    }
    return eventSet;
}

// get event from hashmap with respective dateTime
AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}

// filters attendees on who is free
void AdvancedAgenda::setAttendees(const Event& event, const std::vector<std::string>& attendees) {
    std::vector<std::string> result;
    for(const std::string& attendee : attendees) {
        EventSet* events = getEvents(attendee);
        TimeSpan time = event.getTimeSpan();
        if(!checkOverlap(*events, time)) {
            result.push_back(attendee);
        }
    }
}

// checks for overlaps of TimeSpans => O(n) n = number of events :(
bool AdvancedAgenda::checkOverlap(const EventSet &events, TimeSpan time) {
    for (const Event* event : events) {
        TimeSpan eventTime = event->getTimeSpan();

        if(compareTimes(eventTime.getEndTime(), time.getStartTime())){return true;}
        if(!compareTimes(eventTime.getStartTime(), time.getEndTime())){return true;}
    }
    return false;
}

// returns true if time 1 is before or same as time 2
bool AdvancedAgenda::compareTimes(const DateTime &date1, const DateTime &date2) {
    const int times1[] = {date1.getYear(), date1.getMonth(), date1.getDay(), date1.getHour(), date1.getMin()};
    const int times2[] = {date2.getYear(), date2.getMonth(), date2.getDay(), date2.getHour(), date2.getMin()};

    for (int i = 0; i < 5; i++) {
        if (times1[i] > times2[i]) {return false;}
        if (times1[i] < times2[i]) {return true;}
    }
    return true;
}

void AdvancedAgenda::updateEvent(const std::string& eventName, const std::string& newName, const DateTime &dateTime, const int duration, std::vector<std::string> &attendees) {
    if(getEvents(eventName)->empty()) {
        cout << "Event " << eventName << " does not exist" << endl;
        return;
    }
    std::string description = getEvents(eventName)->begin().operator*()->getDescription();
    const TimeSpan timespan = TimeSpan(dateTime, duration);
    Event newEvent = Event(timespan, description);
    m_eventNameHash[eventName]->erase(getEvents(eventName)->begin());
    m_eventNameHash[eventName]->insert(&newEvent);
}

void AdvancedAgenda::printEvents(const std::string& personName) {
    EventSet* events = getEvents(personName);
    cout << "Events: " << endl;
    for(Event* event : *events) {
        cout << event->toString() << endl;
    }
}
