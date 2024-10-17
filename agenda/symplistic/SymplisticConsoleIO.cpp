//
// Created by robin on 16/10/2024.
//

#include "SymplisticConsoleIO.h"

#include <iostream>
#include "string"

void SymplisticConsoleIO::printEvent(Event *event) {
    std::cout << event->toString();
}