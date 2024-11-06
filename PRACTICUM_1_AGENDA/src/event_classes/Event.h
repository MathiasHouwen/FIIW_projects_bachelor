//
// Created by robin on 16/10/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include "TimeSpan.h"
#include <string>
#include <vector>
using namespace std;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Event {
    private:
        TimeSpan timeSpan;
        std::string description;
        std::vector<std::string> attendees;
    public:
        struct eventComparator{
            bool operator()(Event lhs, Event rhs) const;
        };
        Event(const TimeSpan &time_span, std::string description);
        void changeStartTime(const int hour, const int minute);
        virtual ~Event() = default;
        TimeSpan getTimeSpan() const;
        std::string getDescription() const;
        std::vector<std::string> getAttendees() const;
        void set_attendees(const std::vector<std::string> &attendees);
        std::string toString();
        bool eventsOverlap(Event *event1, Event *event2);
        void addAttendee(const string &attendee);
};


#endif //EVENT_H
