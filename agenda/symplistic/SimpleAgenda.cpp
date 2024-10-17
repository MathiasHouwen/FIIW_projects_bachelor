//
// Created by robin on 16/10/2024.
//

#include "SimpleAgenda.h"
// 2 maps -> map 1 user name > event pointer
// map 2 datetime -> event *
// Event = naam & timespan

// TODO: MAAK LIJST -> op volgorde inserten
// DOORMIDDEL SET
void SimpleAgenda::insertHash(const std::string& name, DateTime dateTime, Event *event) {
    EventSet *setName = m_nameHash[name];
    setName->insert(event);
    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    setDateTime->insert(event);
}

SimpleAgenda::EventSet *SimpleAgenda::getEvents(const string &name) {
    return m_nameHash[name] ;
}

SimpleAgenda::EventSet *SimpleAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}

bool SimpleAgenda::eventComparator::operator()(Event *lhs, Event *rhs) const {
    DateTime first = lhs->getTimeSpan().getStartTime();
    DateTime second = rhs->getTimeSpan().getStartTime();
    if (first.getYear() != second.getYear())
        return first.getYear() < second.getYear();
    if (first.getMonth() != second.getMonth())
        return first.getMonth() < second.getMonth();
    if (first.getDay() != second.getDay())
        return first.getDay() < second.getDay();
    if (first.getHour() != second.getHour())
        return first.getHour() < second.getHour();
    return first.getMin() < second.getMin();
}