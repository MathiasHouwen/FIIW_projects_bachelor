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
bool Scheduler::combineBitMaps(short dateIndex, int year, const vector<string>& attendees, unsigned long long bitmask) {
    unsigned long long bitmap = bitmask;
    for(const string& attendee: attendees){ // O(a)
        MapMidPoint& years = userMap[attendee];
        if(year-years.oldestYear >= years.yearPlans.size()) return true; // niks gepland dat jaar
        auto& map = years.yearPlans[year-years.oldestYear];
        if(!map.contains(dateIndex)) return true; // niks gepland die dag O(1)
        MapEndpoint node = map.get(dateIndex); // O(1)
        bitmap &= node.bitmap; // logische AND verwijderd meteen de niet-overeenkomende slot bits
    }
    return bitmap;
}

// accepteerd een bitmap die al op voorhand ge-and is met time period bitmask.
// bitmap = dus al een everyone-is-free period. Moet gewoon kijken of duration daarin past
char Scheduler::searchFreeSlot(unsigned long long int bitmap, char duration, char startSlot, char endSlot) {
    unsigned long long int mask = (1ULL << duration) - 1; // (macht van 2)-(1) = alle bits onder die macht van 2 op true
    mask <<= startSlot;
    for(char i = startSlot; i <= endSlot - duration; i++){
        if((bitmap & mask) == mask) return i;
        mask <<= 1;
    }
    return -1;
}

// (a*(1+log(e))); a = aantal gekozen attendees, e = aantal data per attendee op de gekozen dag
bool Scheduler::plan(const vector<string>& attendees, const Event& event, const DateTime& endTime, const vector<DateTime>& dates) {
    TimeSpan timeSpan = event.getTimeSpan();
    DateTime startTime = timeSpan.getStartTime();
    unsigned long long planPeriodBitmask = timeAreaToDayBitmask(startTime, endTime);
    unsigned long long negEventBitMask = ~timeAreaToDayBitmask(startTime, timeSpan.getEndTime());
    char startSlot = startTime.getHour() * 2 + (startTime.getMin() / 30);
    char endSlot = endTime.getHour() * 2 + (endTime.getMin() / 30) - 1;

    for(DateTime date : dates){
        short dateIndex = dateToIndex(date);
        int year = date.getYear();
        unsigned long long bitmap = combineBitMaps(dateIndex, year, attendees, planPeriodBitmask); // O(A)
        char slot = searchFreeSlot(bitmap, timeSpan.getDuration(), startSlot, endSlot);
        if(slot == 0) continue;
        auto sharedEventStruct = new MinimalEvent(event);
        for(const string& attendee : attendees){
            insert(attendee, dateIndex, year, sharedEventStruct, negEventBitMask); //log(e)
        }
        return true;
    }
    return false;
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
long long Scheduler::timeAreaToDayBitmask(const DateTime& startTime, const DateTime& endTime) {
    // in timespan = 1 bits, er buiten = 0 bits
    int startSlot = startTime.getHour() * 2 + (startTime.getMin() / 30);
    int endSlot = endTime.getHour() * 2 + (endTime.getMin() / 30) - 1;
    long long bitmap = 0;
    for (int i = startSlot; i <= endSlot; ++i) {
        // logische OR voegt de bits toe
        bitmap |= (1LL << i); //1LL = 1 als long integer (dan werkt de shift altijd op 64bit niveau)
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



