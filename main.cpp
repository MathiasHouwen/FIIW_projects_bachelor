#include <iostream>
#include <string>
#include <unordered_map>

#include "agenda/charedClasses/DateTime.h"
#include "agenda/charedClasses/Event.h"
#include "agenda/charedClasses/TimeSpan.h"
#include "agenda/FileIO.h"
#include "agenda/scheduler/Schedular.h"

using namespace std;

int main() {
//    FileIO io("../events/ALDA practicum 1 - events_small.txt");
//    while(io.hasNext()){
//        FileIO::Entry line = io.nextLine();
//        cout << line.username << ", " << line.event.getDescription() << ", " << line.event.getTimeSpan().getDuration() << endl;
//    }
    Event e1({{30,22,19,10,2024}, 150}, "e1");
    Event e2({{0,13,19,10,2024}, 60}, "e2");
    Event e3({{30,13,19,10,2024}, 60}, "overlap met e2");
    Event e4({{30,13,20,10,2024}, 60}, "zelfde uur als overlap met e2, maar andere dag");

    Schedular schedular;
    const bool schedularTest =
            schedular.plan({"Ebbe", "Robin", "Mathias"}, e1)
            and schedular.plan({"Ebbe", "Mathias"},e2)
            and not schedular.plan({"Ebbe", "Robin"},e3)
            and schedular.plan({"Ebbe", "Robin"},e4)
            and schedular.plan({"Robin"},e3);
    if(!schedularTest) cerr << "schedularTest FAIL" << endl;
    return 0;
}
