//
// Created by robin on 16/10/2024.
//

#include "AdvancedAgenda.h"
// 2 maps -> map 1 user name > event pointer
// map 2 datetime -> event *
// Event = naam & timespan

// TODO: MAAK LIJST -> op volgorde inserten
// DOORMIDDEL SET
void AdvancedAgenda::insertHash(const std::string& name, DateTime dateTime, Event *event) {
    EventSet *setName = m_nameHash[name];
    setName->insert(event);
    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    setDateTime->insert(event);
}

AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(const string &name) {
    return m_nameHash[name] ;
}

AdvancedAgenda::EventSet *AdvancedAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}