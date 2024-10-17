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
