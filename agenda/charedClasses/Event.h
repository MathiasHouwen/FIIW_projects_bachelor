//
// Created by robin on 16/10/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include "TimeSpan.h"
#include <string>
#include <vector>
using namespace std;



class Event {
    private:
        TimeSpan timeSpan;
        std::string description;
        std::vector<std::string> attendees;
    public:
        struct eventComparator{
            bool operator()(Event *lhs, Event *rhs) const;
        };
        Event(const TimeSpan &time_span, std::string description);
        virtual ~Event() = default;

        TimeSpan getTimeSpan();
        std::string getDescription();

        std::vector<std::string> getAttendees() const;

        void setAttendees(const std::vector<std::string> &attendees);
        std::string toString();
};


#endif //EVENT_H
