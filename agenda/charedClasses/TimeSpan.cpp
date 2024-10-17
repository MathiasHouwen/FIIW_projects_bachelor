//
// Created by robin on 16/10/2024.
//

#include "TimeSpan.h"

TimeSpan::TimeSpan(const DateTime &start_time, const int &duration)
            : startTime(start_time),
              duration(duration) {
}

DateTime TimeSpan::getStartTime() const {
    return startTime;
}

int TimeSpan::getDuration() const {
    return duration;
}

DateTime TimeSpan::getEndTime() const {
    int min = startTime.getMin() + duration;

    return checkEndTime(min, startTime.getHour(), startTime.getDay(), startTime.getMonth(), startTime.getYear());
}

DateTime TimeSpan::checkEndTime(int min, int hour, int day, int month, int year) {
    if(min > 59) {
        hour += min / 60;
        min = min % 60;
    }

    if(hour > 23) {
        day += hour / 24;
        hour = hour % 24;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while(day > daysInMonth[month - 1]) {
        day -= daysInMonth[month - 1];
        month++;

        if(month > 12) {
            month = 1;
            year++;
        }
    }

    return {min, hour, day, month, year};
}

