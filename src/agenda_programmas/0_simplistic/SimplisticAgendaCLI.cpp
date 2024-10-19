//
// Created by robin on 16/10/2024.
//

#include "SimplisticAgendaCLI.h"

#include <iostream>
#include "string"

void SimplisticAgendaCLI::printEvent(Event *event) {
    std::cout << event->toString();
}