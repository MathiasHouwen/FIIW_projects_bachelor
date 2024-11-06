//
// Volledig gemaakt door Ebbe
//


#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERSTRUCTS_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERSTRUCTS_H

#include <set>
#include "../../event_classes/Event.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;
struct MinimalEvent{
    unsigned int duration:6;
    unsigned int hour:5;
    unsigned int halfHour:1;
    string description;
    explicit MinimalEvent(const Event& event) :
            description(event.getDescription()),
            duration(event.getTimeSpan().getDuration()/30),
            hour(event.getTimeSpan().getStartTime().getHour()),
            halfHour(event.getTimeSpan().getStartTime().getMin()/30)
    {}
    Event toEvent(const DateTime& date) const{
        return Event({{
            halfHour*30, static_cast<int>(hour),
            date.getDay(), date.getMonth(), date.getYear()},
                      duration*30}, description);
    }
};
struct MinimalEventPointerComparator {
    bool operator()(const MinimalEvent* a, const MinimalEvent* b) const{
        int atime = a->hour*2+a->halfHour;
        int btime = b->hour*2+b->halfHour;
        if(atime != btime){
            return atime < btime;
        }
        return a->description < b->description; // groter of gelijk aan, dus alas gelijk aan wordt ook a gereturnt(=a is laatst toegevoegd)
    };
};
struct MapEndpoint{
    unsigned long long bitmap {static_cast<unsigned long long>(~0LL)}; // 1=vrij 0=event(s) //unsigned puur voor duidelijkheid in debugger
    set<MinimalEvent*, MinimalEventPointerComparator> events;
};
#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERSTRUCTS_H
