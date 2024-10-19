//
// Created by robin on 16/10/2024.
//

#ifndef ADVANCEDAGENDA_H
#define ADVANCEDAGENDA_H

#include <unordered_map>
#include <string>
#include <set>
#include "../charedClasses/Event.h"


class AdvancedAgenda {
public:
    using EventSet = std::set<Event*, Event::eventComparator>;

    void insertHash(const std::string& personName, const std::string&eventName, DateTime dateTime, Event *event);

    EventSet* getEvents(const std::string& name);
    EventSet* getEvents(DateTime dateTime);

    void setAttendees(const Event &event, const std::vector<std::string> &attendees);

    static bool checkOverlap(const EventSet &events, TimeSpan time);

    static bool compareTimes(const DateTime &date1, const DateTime &date2);

    void updateEvent(const std::string& eventName, const std::string& newName, const DateTime &dateTime, int duration, std::vector<std::string> &attendees);

    void printEvents(std::string personName);
private:
    std::unordered_map<std::string, EventSet*> m_eventNameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
    std::unordered_map<std::string, EventSet*> m_personNameHash;
};



#endif //ADVANCEDAGENDA_H