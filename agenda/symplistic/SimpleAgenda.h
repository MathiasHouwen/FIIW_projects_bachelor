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

    void insertHash(const std::string& name, Event *event);
    void insertHash(DateTime dateTime, Event *event);

    Event* getEvent(const std::string& name);
    Event* getEvent(DateTime dateTime);

    std::set <Event*, eventComparator> eventSet;

private:
    std::unordered_map<std::string, Event*> m_nameHash;
    std::unordered_map<std::string, Event*> m_dateTimeHash;
};



#endif //SIMPLEAGENDA_H
