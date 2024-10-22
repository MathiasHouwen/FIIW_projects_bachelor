//
// Created by robin on 16/10/2024.
//

#include "Scheduler.h"
#include "../../util/FileInputReader.h"

#include <utility>

// O(a); a = aatnal gekozen attendees
bool Scheduler::checkAvialability(short dateIndex, int year, const vector<string>& attendees, unsigned long long bitmask) {
    unsigned long long bitmap = bitmask;
    for(const string& attendee: attendees){ // O(a)
        MapMidPoint& years = userMap[attendee];
        if(year-years.oldestYear >= years.yearPlans.size()) return true; // niks gepland dat jaar
        auto& map = years.yearPlans[year-years.oldestYear];
        if(!map.contains(dateIndex)) return true; // niks gepland die dag O(1)
        MapEndpoint node = map.get(dateIndex); // O(1)
        bitmap &= node.bitmap; // logische AND verwijderd meteen de niet-overeenkomende slot bits
    }
    return bitmap == bitmask;
}

// TODO (a*(1+log(e))); a = aantal gekozen attendees, e = aantal data per attendee op de gekozen dag
bool Scheduler::plan(const vector<string>& attendees, const Event& event) {
    TimeSpan timeSpan = event.getTimeSpan();
    DateTime startTime = timeSpan.getStartTime();
    short dateIndex = dateToIndex(startTime);
    int year = startTime.getYear();
    unsigned long long bitmask = timespanToDayBitmask(timeSpan);
    unsigned long long negBitMask = ~bitmask;

    if(!checkAvialability(dateIndex, year, attendees, bitmask)) // O(a)
        return false;

    auto sharedEventStruct = new MinimalEvent(event);
    for(const string& attendee : attendees){
        insert(attendee, dateIndex, year, sharedEventStruct, negBitMask);
    }
    return true;
}

// TODO O(log(e)); e = aantal data van die attendee op die date
void Scheduler::insert(const string& attendee, short dateIndex, int year, MinimalEvent* event, unsigned long long negativeBitmask) {
    MapMidPoint& years = userMap[attendee];
    if(years.oldestYear == 0) years.oldestYear = year;
    if(year-years.oldestYear >= years.yearPlans.size()) {
        years.yearPlans.resize(year-years.oldestYear+1);
    }
    auto& map = years.yearPlans[year-years.oldestYear];
    if (map.contains(dateIndex)){ // O(1)
        MapEndpoint& node = map.get(dateIndex); // O(1)
        node.bitmap &= negativeBitmask;
        node.events.insert(event); // O(log(e))
    }else{
        MapEndpoint node;
        node.bitmap &= negativeBitmask;
        node.events.insert(event); // O(log(e))
        map.insert(dateIndex, node); // TODO O(?)
    }
}

// O(d); d = duration in aantal halve uren
long long Scheduler::timespanToDayBitmask(TimeSpan timeSpan) {
    // in timespan = 1 bits, er buiten = 0 bits
    DateTime startTime = timeSpan.getStartTime();
    int startSlot = startTime.getHour() * 2 + (startTime.getMin() / 30);
    int numOfSlots = timeSpan.getDuration() / 30;
    long long bitmap = 0;
    for (int i = 0; i < numOfSlots; ++i) {
        // logische OR voegt de bits toe
        bitmap |= (1LL << (startSlot + i)); //1LL = 1 als long integer (dan werkt de shift altijd op 64bit niveau)
    }
    return bitmap;
}

void Scheduler::loadFromFile(string filePath) {
    FileInputReader file(filePath);
    while(file.hasNext()){
        FileInputReader::Entry line = file.nextLine();
        plan({line.username}, line.event);
    }
}

list<pair<string, Event>> Scheduler::getSortedAgenda(vector<string> users) {
    return list<pair<string, Event>>();
}

short Scheduler::dateToIndex(DateTime date) {
    return (date.getMonth()- 1)*12 + date.getDay() - 1;
}

