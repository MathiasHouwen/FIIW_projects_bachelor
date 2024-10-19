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
    using EventSet = std::set<Event**, Event::eventComparator>;

    void insertHash(const std::string& personName, const std::string&eventName, DateTime dateTime, Event *event[]);

    EventSet *getEvents(const std::string& name);
    EventSet *getEvents(DateTime dateTime);

private:
    std::unordered_map<std::string, EventSet*> m_eventNameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
    std::unordered_map<std::string, EventSet*> m_personNameHash;
};



#endif //ADVANCEDAGENDA_H