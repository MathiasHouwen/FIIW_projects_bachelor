//
// Created by robin on 16/10/2024.
//

#include "Event.h"
#include <string>


Event::Event(const TimeSpan &time_span, const std::string &description)
            : timeSpan(time_span),
              description(description) {
}

TimeSpan Event::getTimeSpan() {
    return timeSpan;
}

std::string Event::getDescription() {
    return description;
}

std::string Event::toString() {
    return description + " "
        + timeSpan.getStartTime().toString() + " "
        + timeSpan.toString();
}

bool Event::eventComparator::operator()(Event *lhs, Event *rhs) const {
    DateTime first = lhs->getTimeSpan().getStartTime();
    DateTime second = rhs->getTimeSpan().getStartTime();
    if (first.getYear() != second.getYear())
        return first.getYear() < second.getYear();
    if (first.getMonth() != second.getMonth())
        return first.getMonth() < second.getMonth();
    if (first.getDay() != second.getDay())
        return first.getDay() < second.getDay();
    if (first.getHour() != second.getHour())
        return first.getHour() < second.getHour();
    return first.getMin() < second.getMin();
}
