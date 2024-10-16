//
// Created by robin on 16/10/2024.
//

#ifndef EVENTS_H
#define EVENTS_H
#include "TimeSpan.h"
#include <string>
using namespace std;



class Events {
    private:
        TimeSpan timeSpan;
        std::string description;
    public:
        Events(const TimeSpan &time_span, const std::string &description);
        virtual ~Events() = default;

        TimeSpan getTimeSpan();
        std::string getDescription();
};



#endif //EVENTS_H
