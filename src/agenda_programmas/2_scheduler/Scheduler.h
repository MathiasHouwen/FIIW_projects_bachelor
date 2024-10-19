//
// Created by robin on 16/10/2024.
//

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <list>
#include "../../AgendaInterface.h"
#include "../../event_classes/DateTime.h"
#include "../../event_classes/Event.h"

using namespace std;

class Scheduler : public AgendaInterface{
private:
    union DateUnion{
        struct{
            unsigned char day; // geen bit fields nodig want die zouden ook padden tot 4 bytes
            unsigned char month;
            unsigned short year;
        } date;
        explicit DateUnion(DateTime dateTime);
        long asLong;
        bool operator==(const DateUnion& other) const;
        bool operator<(const DateUnion& other) const;
    };
    struct DateUnionHash {
        size_t operator()(const DateUnion& date) const;
    };
    struct MinimalEvent{
        unsigned int duration:6;
        unsigned int hour:5;
        unsigned int halfHour:1;
        string description;
        explicit MinimalEvent(Event event);
    };
    struct MinimalEventPointerComparator {
        bool operator()(const MinimalEvent* a, const MinimalEvent* b) const;
    };
    struct MapEndpoint{
        unsigned long long bitmap {static_cast<unsigned long long>(~0LL)}; // 1=vrij 0=event(s) //unsigned puur voor duidelijkheid in debugger
        set<MinimalEvent*, MinimalEventPointerComparator> events;
    };
    struct InnerMapContainer{
        unordered_map<DateUnion, MapEndpoint, DateUnionHash> map{};
        set<DateUnion> set{};
    };
    unordered_map<string, InnerMapContainer> outerMap{};
    bool checkAvialability(TimeSpan timeSpan, DateUnion date, vector<string> attendees, long long bitmask);
    void insert(const string& attendee, DateUnion date, MinimalEvent* event, long long bitmask);
    static long long timespanToDayBitmask(TimeSpan timeSpan);
public:
    bool plan(vector<string> attendees, Event event);// bool voor "is gelukt" / "geen avialability"
    list<pair<string, Event>> getSortedAgenda(vector<string> users);
    void loadFromFile(string filePath) override;
};

#endif //SCHEDULAR_H
