//
// Created by robin on 16/10/2024.
//

#ifndef SIMPLEAGENDA_H
#define SIMPLEAGENDA_H


#include <unordered_map>
#include <string>
#include "../charedClasses/Event.h"

class SimpleAgenda {
public:
    void insertHash(const std::string& name, Event *event);
    void insertHash(DateTime dateTime, Event *event);

    Event* getEvent(const std::string& name);
    Event* getEvent(DateTime dateTime);
private:
    std::unordered_map<std::string, Event*> m_nameHash;
    std::unordered_map<std::string, Event*> m_dateTimeHash;
};



#endif //SIMPLEAGENDA_H
