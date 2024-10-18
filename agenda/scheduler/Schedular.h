//
// Created by robin on 16/10/2024.
//

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <unordered_map>
#include <string>
#include <vector>
#include "../charedClasses/TimeSpan.h"

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
        std::size_t operator()(const DateUnion& date) const {
            return std::hash<long>()(date.asLong);
        }
    };
    struct MapNode{
        MapNode* next {nullptr};
        long long bitmap:48 {0};
    };
    unordered_map<string, unordered_map<DateUnion, MapNode, DateUnionHash>> userDateMap{};
    bool checkAvialability(TimeSpan timeSpan, vector<string> attendees);
    static long long timespanToDayBitmask(TimeSpan timeSpan);
public:
    void addUser(string userName);
};

#endif //SCHEDULAR_H
