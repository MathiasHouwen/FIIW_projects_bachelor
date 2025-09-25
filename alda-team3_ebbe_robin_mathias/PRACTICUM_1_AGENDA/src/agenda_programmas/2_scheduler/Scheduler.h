//
// Volledig gemaakt door Ebbe
//

#ifndef SCHEDULAR_H
#define SCHEDULAR_H


#include <unordered_map>
#include <list>
#include "PointlessMap.h"
#include "SchedulerStructs.h"
#include "../../AgendaInterface.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;

class Scheduler : public AgendaInterface{
public:
    bool plan(const vector<string>& attendees, const Event& event, const DateTime& endTime, const vector<DateTime>& dates);// bool voor "is gelukt" / "geen avialability"
    bool planSingleDayNoEndTime(const vector<string>& attendees, const Event& event);
    list<Event> getSortedAgenda(const vector<string>& users);
    void loadFromFile(string filePath) override;
private:
    struct MapMidPoint{
        int oldestYear{0};
        vector<PointlessMap<MapEndpoint>> yearPlans{};
    };
    int globalOldestYear{9999};
    int globalNewestYear{0};
    unordered_map<string, MapMidPoint> userMap{};
    unsigned long long combineBitMaps(short dateIndex, int year, const vector<string>& attendees, unsigned long long bitmask);
    void insert(const string& attendee, short dateIndex, int year, MinimalEvent* event, unsigned long long bitmask);
    char searchFreeSlot(unsigned long long bitmap, char duration, char startSlot, char endSlot);
    static long long timeAreaToDayBitmask(const DateTime& startTime, const DateTime& endTime);
    static short dateToIndex(const DateTime& date);
    static DateTime indexToDate(short dateIndex, int year);
};

#endif //SCHEDULAR_H
