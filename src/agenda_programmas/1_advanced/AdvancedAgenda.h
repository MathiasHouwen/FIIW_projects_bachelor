//
// Volledig gemaakt door Robin
//
#ifndef ADVANCEDAGENDA_H
#define ADVANCEDAGENDA_H

#include <unordered_map>
#include <string>
#include <set>
#include "../../event_classes/Event.h"
#include "../../AgendaInterface.h"
#include "../../util/FileInputReader.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class AdvancedAgenda : public AgendaInterface{
public:
    using EventSet = std::set<Event, Event::eventComparator>;

    void insertHash(const std::string& personName, const std::string&eventName, DateTime dateTime, Event event);
    void eraseHash(Event event, std::string personName);

    EventSet* getEvents(const std::string& name);
    EventSet* getEvents(DateTime dateTime);

    void setFilteredAttendees(Event &event, const std::vector<std::string> &attendees);

    static bool checkOverlap(const EventSet &events, const Event& event);

    static bool compareTimes(const TimeSpan &time1, const TimeSpan &time2);

    void loadFromFile(string filePath) override;
    void updateEvent(const std::string& eventName, const std::string& newName, const DateTime &dateTime, int duration, std::vector<std::string> &attendees);

    void printEvents(const std::string& personName);

    void linkAttendees(std::vector<std::string> &attendees, Event event);

    void removeAttendees(std::vector<std::string> &attendees, Event event);

private:
    std::unordered_map<std::string, EventSet*> m_eventNameHash;
    std::unordered_map<std::string, EventSet*> m_dateTimeHash;
    std::unordered_map<std::string, EventSet*> m_personNameHash;
};



#endif //ADVANCEDAGENDA_H