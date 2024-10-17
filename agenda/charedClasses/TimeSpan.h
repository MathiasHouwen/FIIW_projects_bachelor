//
// Created by robin on 16/10/2024.
//

#ifndef TIMESPAN_H
#define TIMESPAN_H
#include "DateTime.h"


class TimeSpan {
    private:
        DateTime startTime;
        int duration;
        static DateTime checkEndTime(int min, int hour, int day, int month, int year);
    public:
        TimeSpan(const DateTime &start_time, const int &duration);
        DateTime getStartTime() const;
        int getDuration() const;
        DateTime getEndTime() const;
};



#endif //TIMESPAN_H
