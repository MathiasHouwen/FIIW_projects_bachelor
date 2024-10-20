//
// Created by robin on 16/10/2024.
//

#include "SimplisticAgenda.h"
#include "../../util/FileInputReader.h"
// 2 maps -> map 1 user name > event pointer
// map 2 datetime -> event *
// Event = naam & timespan

void SimplisticAgenda::insertHash(const std::string& name, DateTime dateTime, Event event) {
    EventSet *setName = m_nameHash[name];
    if (!setName) {
        setName = new EventSet();
        m_nameHash[name] = setName;
    }
    setName->insert(event);

    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    if (!setDateTime) {
        setDateTime = new EventSet();
        m_dateTimeHash[dateTime.toString()] = setDateTime;
    }
    setDateTime->insert(event);
}

bool SimplisticAgenda::insertEvent(const std::string& name, DateTime dateTime, Event event){
    EventSet* setName = m_nameHash[name];
    if (!setName) {
        setName = new EventSet(); // Create a new set if none exists for this name
        m_nameHash[name] = setName;
    } else if (checkOverlap(*setName, event.getTimeSpan())) {
        return false;
    }

    insertHash(name, dateTime, event);
    return true;
}

SimplisticAgenda::EventSet *SimplisticAgenda::getEvents(const string &name) {
    return m_nameHash[name] ;
}

SimplisticAgenda::EventSet *SimplisticAgenda::getEvents(DateTime dateTime) {
    return m_dateTimeHash[dateTime.toString()];
}

void SimplisticAgenda::loadFromFile(string filePath) {
    FileInputReader file(filePath);
    while(file.hasNext()){
        FileInputReader::Entry line = file.nextLine();
        Event event = line.event;
        insertEvent(line.username, line.event.getTimeSpan().getStartTime(), line.event);
    }
}

bool SimplisticAgenda::checkOverlap(const EventSet &events, TimeSpan time) {
    for (const Event event : events) {
        if(compareTimes(event.getTimeSpan(), time)){
            return true;
        }
    }
    return false;
}

bool SimplisticAgenda::compareTimes(const TimeSpan &time1, const TimeSpan &time2) {
    DateTime thisStart = time1.getStartTime();
    DateTime thisEnd = time1.getEndTime();
    DateTime otherStart = time2.getStartTime();
    DateTime otherEnd = time2.getEndTime();

    return (thisStart < otherEnd) && (otherStart < thisEnd);
}