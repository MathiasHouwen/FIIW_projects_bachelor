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
    using EventSet = std::set<Event*, eventComparator>;

    void insertHash(const std::string& name, DateTime dateTime, Event *event);

    EventSet *getEvents(const std::string& name);
    EventSet *getEvents(DateTime dateTime);

private:
    std::unordered_map<std::string, EventSet*> m_nameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
};



#endif //ADVANCEDAGENDA_H