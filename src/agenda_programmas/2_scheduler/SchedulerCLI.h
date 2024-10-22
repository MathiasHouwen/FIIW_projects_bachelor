//
// Created by ebbew on 19-10-2024.
//

#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H


#include "../../util/CLIInterface.h"
#include "Scheduler.h"

class SchedulerCLI: CLIInterface {
private:
    Scheduler scheduler;
    bool isDateTimeInput(const std::string &input);
public:
    explicit SchedulerCLI(const Scheduler &scheduler);
    void getInput() override;
    void plan();
    void print();
};


#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H
