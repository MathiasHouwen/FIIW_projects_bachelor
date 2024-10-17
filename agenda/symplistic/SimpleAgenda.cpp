//
// Created by robin on 16/10/2024.
//

#include "SimpleAgenda.h"
// 2 maps -> map 1 user name > event pointer
// map 2 datetime -> event *
// Event = naam & timespan

void SimpleAgenda::insertHash(const std::string& name, Event *event) {
    m_nameHash[name] = event;
}

void SimpleAgenda::insertHash(DateTime dateTime, Event *event) {
    m_dateTimeHash[dateTime] = event;
}

Event *SimpleAgenda::getEvent(const string &name) {
    return m_nameHash[name];
}

Event *SimpleAgenda::getEvent(DateTime dateTime) {
    return m_dateTimeHash[dateTime];
}
