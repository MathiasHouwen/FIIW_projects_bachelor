//
// Volledig gemaakt door Mathias
//

#include "SimplisticAgenda.h"
#include "../../util/FileInputReader.h"
// 2 maps -> map 1 user name > event pointer
// map 2 datetime -> event *
// Event = naam & timespan

// O(logN + OlogM),
// => O(logN) because there are relative little elements in the set.
void SimplisticAgenda::insertHash(const std::string& name, DateTime dateTime, Event event) {
    EventSet *setName = m_nameHash[name]; //O(1)
    if (!setName) { //O(1)
        setName = new EventSet();
        m_nameHash[name] = setName;
    }
    setName->insert(event); //O(logN)

    EventSet *setDateTime = m_dateTimeHash[dateTime.toString()];
    if (!setDateTime) {
        setDateTime = new EventSet();
        m_dateTimeHash[dateTime.toString()] = setDateTime;
    }
    setDateTime->insert(event); //O(logM)
}

// O(logN)
bool SimplisticAgenda::insertEvent(const std::string& name, DateTime dateTime, Event event){
    EventSet* setName = m_nameHash[name];
    if (!setName) {
        setName = new EventSet(); // Create a new set if none exists for this name
        m_nameHash[name] = setName;
    }
    else if (checkOverlap(*setName, event)) {
        return false;
    }

    event.addAttendee(name);

    insertHash(name, dateTime, event);
    return true;
}
// average: O(1), worst: O(n) should not happen only if there are only hash collisions
SimplisticAgenda::EventSet *SimplisticAgenda::getEvents(const string &name) {
    return m_nameHash[name] ;
}

// average: O(1), worst: O(n) should not happen only if there are only hash collisions
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

// Because of the lower_bound overall time complexity is O(logN)
// The rest of the function has O(1).
bool SimplisticAgenda::checkOverlap(const EventSet &events, Event event) {
    auto higher = events.lower_bound(event); // O(logN)
    if (higher != events.end() && compareTimes(higher->getTimeSpan(), event.getTimeSpan())) {
        return true;
    }
    if (higher != events.begin()) {
        auto lower = std::prev(higher);
        if(compareTimes(lower->getTimeSpan(), event.getTimeSpan())) return true;
    }
    return false;
}

// O(1)
bool SimplisticAgenda::compareTimes(const TimeSpan &time1, const TimeSpan &time2) {
    DateTime thisStart = time1.getStartTime();
    DateTime thisEnd = time1.getEndTime();
    DateTime otherStart = time2.getStartTime();
    DateTime otherEnd = time2.getEndTime();

    return (thisStart < otherEnd) && (otherStart < thisEnd);
}