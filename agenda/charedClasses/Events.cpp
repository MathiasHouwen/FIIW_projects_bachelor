//
// Created by robin on 16/10/2024.
//

#include "Events.h"

Events::Events(const TimeSpan &time_span, const std::string &description)
            : timeSpan(time_span),
              description(description) {
}

TimeSpan Events::getTimeSpan() {
    return timeSpan;
}

std::string Events::getDescription() {
    return description;
}
