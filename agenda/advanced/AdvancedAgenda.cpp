//
// Created by robin on 16/10/2024.
//

#include "AdvancedAgenda.h"
// 2 maps -> map 1 user name > list of event pointers
// map 2 datetime -> list<event*>
// Event = naam & timespan

// TODO: MAAK LIJST -> op volgorde inserten
// DOORMIDDEL SET
void AdvancedAgenda::insertHash(const std::string& personName, const std::string& eventName, DateTime dateTime, Event* event[]) {
    EventSet *setEventName = m_eventNameHash[eventName];
    setEventName->insert(event);
    EventSet *setPersonName = m_eventNameHash[eventName];
    setPersonName->insert(event);
    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    setDateTime->insert(event);
}

AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(const string &name) {
    AdvancedAgenda::EventSet *eventSet = m_eventNameHash[name];
    if (eventSet->empty()) {
        return m_personNameHash[name];
    }
    return eventSet;
}

AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}