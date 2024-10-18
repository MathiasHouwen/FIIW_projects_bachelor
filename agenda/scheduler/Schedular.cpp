//
// Created by robin on 16/10/2024.
//

#include "Schedular.h"

bool Schedular::checkAvialability(TimeSpan timeSpan, vector<string> attendees) {
    // bitmask van de gewenste timeslot
    long long bitmask = timespanToDayBitmask(timeSpan);
    DateUnion date{timeSpan.getStartTime()};


    for(const string& attendee: attendees){
        MapNode node = userDateMap[attendee][date];
        bitmask &= node.bitmap; // logische and verwijderd meteen de niet-overeenkomende slot bits
    }
    return bitmask != 0;
}

void Schedular::addUser(string userName) {
    // create a new inner map
    userDateMap[userName] = unordered_map<DateUnion, MapNode, DateUnionHash> {};
}

long long Schedular::timespanToDayBitmask(TimeSpan timeSpan) {
    DateTime startTime = timeSpan.getStartTime();
    int startSlot = startTime.getHour() * 2 + (startTime.getMin() / 30);
    int numOfSlots = (timeSpan.getDuration() + 29) / 30;
    long long bitmap = 0;
    for (int i = 0; i < numOfSlots; ++i) {
        bitmap |= (1LL << (startSlot + i)); //1LL = 1 als long integer (dan werkt de shift altijd op 64bit niveau)
    }
    // om and te gebruiken om vrije periodes te vinden,
    //moeten vrije slots 1 zijn, dus nog inverten:
    return ~bitmap;
}

Schedular::DateUnion::DateUnion(DateTime dateTime)
        : date(static_cast<char>(dateTime.getDay()),static_cast<char>(dateTime.getMonth()), static_cast<short>(dateTime.getYear()))
{}

bool Schedular::DateUnion::operator==(const Schedular::DateUnion &other) const {
    return asLong == other.asLong;
}
