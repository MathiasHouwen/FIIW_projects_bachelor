//
// Created by robin on 16/10/2024.
//

#ifndef SIMPLEAGENDA_H
#define SIMPLEAGENDA_H


#include <unordered_map>
#include <string>
#include <set>
#include "../charedClasses/Event.h"

class SimpleAgenda {
public:
    struct eventComparator{
        bool operator()(Event *lhs, Event *rhs) const;
    };
    using EventSet = std::set<Event*, eventComparator>;

    void insertHash(const std::string& name, DateTime dateTime, Event *event);

    EventSet *getEvents(const std::string& name);
    EventSet *getEvents(DateTime dateTime);

private:
    std::unordered_map<std::string, EventSet*> m_nameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
};



#endif //SIMPLEAGENDA_H
