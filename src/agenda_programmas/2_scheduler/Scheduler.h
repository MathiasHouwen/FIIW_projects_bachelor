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
    bool plan(vector<string> attendees, Event event);// bool voor "is gelukt" / "geen avialability"
    list<pair<string, Event>> getSortedAgenda(vector<string> users);
    void loadFromFile(string filePath) override;
private:
    unordered_map<string, PointlessMap<MapEndpoint>> userMap{};
    bool checkAvialability(TimeSpan timeSpan, DateTime date, vector<string> attendees, long long bitmask);
    void insert(const string& attendee, DateTime date, MinimalEvent* event, long long bitmask);
    static long long timespanToDayBitmask(TimeSpan timeSpan);
    static short dateToShort(DateTime date);
};

#endif //SCHEDULAR_H
