//
// Volledig gemaakt door Ebbe
//


#include "Scheduler.h"
#include "../../util/FileInputReader.h"

#include <utility>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

// (a*(1+log(e))); a = aantal gekozen attendees, e = aantal data per attendee op de gekozen dag
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
        insert(attendee, dateIndex, year, sharedEventStruct, negBitMask); //log(e)
    }
    return true;
}

// O(log(e)); e = aantal data van die attendee op die date
// pointlessmap insert is verwaarloosbaar
void Scheduler::insert(const string& attendee, short dateIndex, int year, MinimalEvent* event, unsigned long long negativeBitmask) {
    MapMidPoint& years = userMap[attendee];
    if(years.oldestYear == 0 || year < years.oldestYear) years.oldestYear = year;
    if(year < globalOldestYear) globalOldestYear = year;
    if(year > globalNewestYear) globalNewestYear = year;
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
        map.insert(dateIndex, node); // bijna O(1)
    }
}

// O(d); d = duration in aantal halve uren
long long Scheduler::timespanToDayBitmask(const TimeSpan& timeSpan) {
    // in timespan = 1 bits, er buiten = 0 bits
    const DateTime& startTime = timeSpan.getStartTime();
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

// O(out*log(e)) out = aantal outputs (=O(1) navigatie), e = gemiddeld aantal events per user per dag
list<Event> Scheduler::getSortedAgenda(const vector<string>& users) {
    list<Event> result{};
    for(int year=globalOldestYear; year <=globalNewestYear; year++){
        bool noPlansThisYear = true;
        short lastDate = -1;
        short currentDate = 9999;
        bool firstDate = true;
        bool reachedEnd = false;
        while (!reachedEnd){
            set<MinimalEvent*, MinimalEventPointerComparator> events{};
            bool firstUser = true;
            for(string user : users){ // O(users)
                MapMidPoint& years = userMap[user];
                // year bestaat niet voor die user:
                if(year < years.oldestYear || year > years.yearPlans.size() - years.oldestYear) continue;
                // year heeft geen plannen voor die user:
                auto& map = years.yearPlans[year-years.oldestYear];
                if(map.isEmpty()) continue; // O(1)
                noPlansThisYear = false;

                if(firstDate){
                    short first = map.getFirstIndex();
                    short last = map.getLastIndex();
                    if(first < currentDate) currentDate = first;
                    if(last > lastDate) lastDate = last;
                } else {
                    short nextUserDate = map.getNext(currentDate);
                    if(firstUser) currentDate = nextUserDate;
                    else if(currentDate!=lastDate && nextUserDate < currentDate) currentDate = nextUserDate;
                }
                firstUser = false;
                if(!map.contains(currentDate)) continue;
                auto& dayPlan = map.get(currentDate).events;

                for(MinimalEvent* event : dayPlan){
                    events.insert(event);
                }
            }
            firstDate = false;
            reachedEnd = currentDate >= lastDate;
            if(noPlansThisYear) break;
            for(MinimalEvent* minimalEvent : events){
                result.push_back(minimalEvent->toEvent(indexToDate(currentDate, year)));
            }
        }
    }
    return result;
}

short Scheduler::dateToIndex(const DateTime& date) {
    return (date.getMonth()- 1)*12 + date.getDay() - 1;
}

DateTime Scheduler::indexToDate(short dateIndex, int year) {
    int monthIndex = (dateIndex-29) / 12 + 1;
    if(monthIndex>11) monthIndex = 11;
    int dayIndex = dateIndex - 12 * monthIndex;
    return {-1,dayIndex+1,monthIndex+1,year};
}

