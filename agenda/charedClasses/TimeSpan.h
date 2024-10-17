//
// Created by robin on 16/10/2024.
//

#ifndef TIMESPAN_H
#define TIMESPAN_H
#include "DateTime.h"
#include <string>


class TimeSpan {
    private:
        DateTime startTime;
        DateTime duration;
        static DateTime checkEndTime(int min, int hour, int day, int month, int year);

        int durationInMinutes();
    public:
        TimeSpan(const DateTime &start_time, const DateTime &duration);
        DateTime getStartTime() const;
        DateTime getDuration() const;
        DateTime getEndTime() const;

        std::string toString();
};



#endif //TIMESPAN_H
