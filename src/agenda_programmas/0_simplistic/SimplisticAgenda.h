//
// Created by robin on 16/10/2024.
//

#ifndef SIMPLEAGENDA_H
#define SIMPLEAGENDA_H


#include <unordered_map>
#include <string>
#include <set>
#include "../../event_classes/Event.h"
#include "../../AgendaInterface.h"

class SimplisticAgenda : public AgendaInterface {
public:

    using EventSet = std::set<Event*, Event::eventComparator>;

    void insertHash(const std::string& name, DateTime dateTime, Event *event);

    EventSet *getEvents(const std::string& name);
    EventSet *getEvents(DateTime dateTime);
    void loadFromFile() override;

private:
    std::unordered_map<std::string, EventSet*> m_nameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
};



#endif //SIMPLEAGENDA_H
