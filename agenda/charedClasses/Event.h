//
// Created by robin on 16/10/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include "TimeSpan.h"
#include <string>
using namespace std;



class Event {
    private:
        TimeSpan timeSpan;
        std::string description;
    public:
        Event(const TimeSpan &time_span, const std::string &description);
        virtual ~Event() = default;

        TimeSpan getTimeSpan();
        std::string getDescription();

        std::string toString();
};


#endif //EVENT_H
