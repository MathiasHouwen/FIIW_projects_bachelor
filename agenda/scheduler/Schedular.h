//
// Created by robin on 16/10/2024.
//

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include "../charedClasses/TimeSpan.h"
#include "../charedClasses/Event.h"

using namespace std;

class Schedular {
private:
    union DateUnion{
        struct{
            char day; // geen bit fields nodig want die zouden ook padden tot 4 bytes
            char month;
            short year;
        } date;
        explicit DateUnion(DateTime dateTime);
        long asLong;
        bool operator==(const DateUnion& other) const;
    };
    struct DateUnionHash {
        std::size_t operator()(const DateUnion& date) const;
    };
    struct MinimalEvent{
        int duration:6;
        int hour:5;
        int halfHour:1;
        string description;
        explicit MinimalEvent(Event event);
    };
    struct MinimalEventComparator {
        bool operator()(const MinimalEvent* a, const MinimalEvent* b) const;
    };
    struct MapNode{
        MapNode* next {nullptr};
        long long bitmap:48 {~0LL}; // 1=vrij 0=event(s)
        set<MinimalEvent*, MinimalEventComparator> events;
    };
    unordered_map<string, unordered_map<DateUnion, MapNode, DateUnionHash>> userDateMap{};
    bool checkAvialability(TimeSpan timeSpan, DateUnion date, vector<string> attendees, long long bitmask);
    void insert(const string& attendee, DateUnion date, MinimalEvent* event, long long bitmask);
    static long long timespanToDayBitmask(TimeSpan timeSpan);
public:
    bool plan(vector<string> attendees, Event event); // bool voor "is gelukt" / "geen avialability"
};

#endif //SCHEDULAR_H
