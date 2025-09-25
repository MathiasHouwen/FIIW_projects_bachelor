//
// Volledig gemaakt door Ebbe
//


#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H


#include "../../util/CLIInterface.h"
#include "Scheduler.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class SchedulerCLI: CLIInterface {
private:
    Scheduler* scheduler;
    bool isDateTimeInput(const std::string &input);
public:
    explicit SchedulerCLI(Scheduler* scheduler);
    void getInput() override;
    void plan();
    void print();
};


#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_SCHEDULERCLI_H
