#include <iostream>
#include <string>

#include "agenda/charedClasses/DateTime.h"
#include "agenda/charedClasses/Event.h"
#include "agenda/charedClasses/TimeSpan.h"
using namespace std;

int main() {
    DateTime start(30, 22, 21, 6, 2004);
    DateTime duration(40, 4, 20, 5, 20);
    TimeSpan timespan(start, duration);
    Event robinsLeven(timespan, "robinsLeven");
    cout << robinsLeven.getDescription() << endl;
    cout << "jaar: " << robinsLeven.getTimeSpan().getEndTime().getYear() << endl;
    cout << "maand: " << robinsLeven.getTimeSpan().getEndTime().getMonth() << endl;
    cout << "dag: " << robinsLeven.getTimeSpan().getEndTime().getDay() << endl;
    cout << "uur: " << robinsLeven.getTimeSpan().getEndTime().getHour() << endl;
    cout << "minuten: " << robinsLeven.getTimeSpan().getEndTime().getMin() << endl;

    cout << "tostring test" << endl;
    cout <<  robinsLeven.toString();
    return 0;
}
