//
// Created by robin on 16/10/2024.
//

#ifndef SCHEDULAR_H
#define SCHEDULAR_H


#include <list>
#include <unordered_map>
#include "PointlessMap.h"
#include "SchedulerStructs.h"
#include "../../AgendaInterface.h"

using namespace std;

class Scheduler : public AgendaInterface{
public:
    bool plan(const vector<string>& attendees, const Event& event);// bool voor "is gelukt" / "geen avialability"
    list<pair<string, Event>> getSortedAgenda(vector<string> users);
    void loadFromFile(string filePath) override;
private:
    struct MapMidPoint{
        int oldestYear{0};
        vector<PointlessMap<MapEndpoint>> yearPlans{};
    };
    unordered_map<string, MapMidPoint> userMap{};
    bool checkAvialability(short dateIndex, int year, const vector<string>& attendees, unsigned long long bitmask);
    void insert(const string& attendee, short dateIndex, int year, MinimalEvent* event, unsigned long long bitmask);
    static long long timespanToDayBitmask(TimeSpan timeSpan);
    static short dateToIndex(DateTime date);
};

#endif //SCHEDULAR_H
