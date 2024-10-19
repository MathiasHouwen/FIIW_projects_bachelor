//
// Created by robin on 16/10/2024.
//

#include "Scheduler.h"
#include "../../util/FileInputReader.h"

#include <utility>

// O(a); a = aatnal gekozen attendees
bool Scheduler::checkAvialability(TimeSpan timeSpan, DateUnion date, vector<string> attendees, long long bitmask) {
    long long bitmap = bitmask;
    for(const string& attendee: attendees){
        MapEndpoint& node = outerMap[attendee].map[date];
        bitmap &= node.bitmap; // logische AND verwijderd meteen de niet-overeenkomende slot bits
    }
    return bitmap == bitmask;
}

// O(a*(1+log(e))); a = aantal gekozen attendees, e = aantal data per attendee op de gekozen dag
bool Scheduler::plan(vector<string> attendees, Event event) {
    TimeSpan timeSpan = event.getTimeSpan();
    DateUnion date{timeSpan.getStartTime()};
    long long bitmask = timespanToDayBitmask(timeSpan);
    long long negBitMask = ~bitmask;

    if(!checkAvialability(timeSpan, date, attendees, bitmask))
        return false;

    auto sharedEventStruct = new MinimalEvent(event);
    for(const string& attendee : attendees){
        insert(attendee, date, sharedEventStruct, negBitMask);
    }
    return true;
}

// O(log(e)); e = aantal data van die attendee op die date
void Scheduler::insert(const string& attendee, DateUnion date, MinimalEvent* event, long long negativeBitmask) {
    InnerMapContainer& inner = outerMap[attendee];
    if(!inner.map.contains(date)) // de map en set zijn gesynchroniseerd -> sneller om in map te kijken om set insert te vermijden
        inner.set.insert(date); // LOG(N)
    MapEndpoint& node = inner.map[date]; // als niet bestaat word node automatich ge-construct
    node.bitmap &= negativeBitmask;
    node.events.insert(event);
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

Scheduler::DateUnion::DateUnion(DateTime dateTime)
        : date(static_cast<char>(dateTime.getDay()),static_cast<char>(dateTime.getMonth()), static_cast<short>(dateTime.getYear()))
{}

bool Scheduler::DateUnion::operator==(const Scheduler::DateUnion &other) const {
    return asLong == other.asLong;
}



Scheduler::MinimalEvent::MinimalEvent(Event event) :
    description(event.getDescription()),
    duration(event.getTimeSpan().getDuration()/30),
    hour(event.getTimeSpan().getStartTime().getHour()),
    halfHour(event.getTimeSpan().getStartTime().getMin()/30)
{}

std::size_t Scheduler::DateUnionHash::operator()(const Scheduler::DateUnion &date) const {
    return std::hash<long>()(date.asLong);
}

bool Scheduler::MinimalEventPointerComparator::operator()(const Scheduler::MinimalEvent* a,
                                                          const Scheduler::MinimalEvent* b) const {
    int atime = a->hour*2+a->halfHour;
    int btime = b->hour*2+b->halfHour;
    if(atime != btime){
        return atime < btime;
    }
    return a->description < b->description;
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


bool Scheduler::DateUnion::operator<(const Scheduler::DateUnion &other) const {
    if(date.year != other.date.year) return date.year < other.date.year;
    if(date.month != other.date.month) return date.month < other.date.month;
    if(date.day != other.date.day) return date.day < other.date.day;
    return false;
}
