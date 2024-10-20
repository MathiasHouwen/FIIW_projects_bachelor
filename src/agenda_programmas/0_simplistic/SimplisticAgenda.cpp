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
    }

//    if (checkOverlap(*setName, event.getTimeSpan())) {
//        return false;
//    }

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

// checks for overlaps of TimeSpans => O(n) n = number of events :(
bool SimplisticAgenda::checkOverlap(const EventSet &events, TimeSpan time) {
    for (const Event event : events) {
        TimeSpan eventTime = event.getTimeSpan();

        if(compareTimes(eventTime.getEndTime(), time.getStartTime())){return true;}
        if(!compareTimes(eventTime.getStartTime(), time.getEndTime())){return true;}
    }
    return false;
}

// returns true if time 1 is before or same as time 2
bool SimplisticAgenda::compareTimes(const DateTime &date1, const DateTime &date2) {
    const int times1[] = {date1.getYear(), date1.getMonth(), date1.getDay(), date1.getHour(), date1.getMin()};
    const int times2[] = {date2.getYear(), date2.getMonth(), date2.getDay(), date2.getHour(), date2.getMin()};

    for (int i = 0; i < 5; i++) {
        if (times1[i] > times2[i]) {return false;}
        if (times1[i] < times2[i]) {return true;}
    }
    return true;
}