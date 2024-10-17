#include <iostream>

#include "agenda/charedClasses/DateTime.h"
#include "agenda/charedClasses/Event.h"
#include "agenda/charedClasses/TimeSpan.h"
#include "agenda/FileIO.h"

using namespace std;

int main() {
//    DateTime start(30, 22, 21, 6, 2004);
//    TimeSpan timespan(start, 40);
//    Event robinsLeven(timespan, "dit is de berekende DateTime:");
//    cout << robinsLeven.getDescription() << endl;
//    cout << "jaar: " << robinsLeven.getTimeSpan().getEndTime().getYear() << endl;
//    cout << "maand: " << robinsLeven.getTimeSpan().getEndTime().getMonth() << endl;
//    cout << "dag: " << robinsLeven.getTimeSpan().getEndTime().getDay() << endl;
//    cout << "uur: " << robinsLeven.getTimeSpan().getEndTime().getHour() << endl;
//    cout << "minuten: " << robinsLeven.getTimeSpan().getEndTime().getMin() << endl;
    FileIO io("../events/ALDA practicum 1 - events_small.txt");
    while(io.hasNext()){
        FileIO::Entry line = io.nextLine();
        cout << line.username << ", " << line.event.getDescription() << ", " << line.event.getTimeSpan().getDuration() << endl;
    }
    return 0;
}
