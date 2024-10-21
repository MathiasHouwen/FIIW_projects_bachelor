//
// Created by robin on 16/10/2024.
//

#include "Scheduler.h"
#include "../../util/FileInputReader.h"

#include <utility>

// O(a); a = aatnal gekozen attendees
bool Scheduler::checkAvialability(TimeSpan timeSpan, DateTime date, vector<string> attendees, long long bitmask) {
    long long bitmap = bitmask;
    for(const string& attendee: attendees){
        //MapEndpoint& node = outerMap[attendee].map[date];
        //bitmap &= node.bitmap; // logische AND verwijderd meteen de niet-overeenkomende slot bits
    }
    return bitmap == bitmask;
}

// O(a*(1+log(e))); a = aantal gekozen attendees, e = aantal data per attendee op de gekozen dag
bool Scheduler::plan(vector<string> attendees, Event event) {
    TimeSpan timeSpan = event.getTimeSpan();
    //DateTime date{timeSpan.getStartTime()};
    long long bitmask = timespanToDayBitmask(timeSpan);
    long long negBitMask = ~bitmask;

//    if(!checkAvialability(timeSpan, date, attendees, bitmask))
//        return false;

    auto sharedEventStruct = new MinimalEvent(event);
//    for(const string& attendee : attendees){
//        insert(attendee, date, sharedEventStruct, negBitMask);
//    }
    return true;
}

// O(log(e)); e = aantal data van die attendee op die date
void Scheduler::insert(const string& attendee, DateTime date, MinimalEvent* event, long long negativeBitmask) {
    //InnerMapContainer& inner = outerMap[attendee];
//    if(!inner.map.contains(date)) // de map en set zijn gesynchroniseerd -> sneller om in map te kijken om set insert te vermijden
//        inner.set.insert(date); // LOG(N)
//    MapEndpoint& node = inner.map[date]; // als niet bestaat word node automatich ge-construct
//    node.bitmap &= negativeBitmask;
//    node.events.insert(event);
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

short Scheduler::dateToShort(DateTime date) {
    return date.getMonth()*12 + date.getDay();
}

