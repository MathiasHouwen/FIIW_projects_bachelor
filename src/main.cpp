#include <iostream>
#include <chrono>
#include "event_classes/Event.h"
#include "agenda_programmas/2_scheduler/Scheduler.h"
#include "util/FileInputReader.h"
#include "agenda_programmas/0_simplistic/SimplisticAgenda.h"
#include "agenda_programmas/0_simplistic/SimplisticAgendaCLI.h"
#include "agenda_programmas/1_advanced/AdvancedAgenda.h"
#include "agenda_programmas/1_advanced/AdvancedAgendaCLI.h"
#include "agenda_programmas/2_scheduler/PointlessMap.h"

using namespace std;
using d = chrono::duration<float, std::milli>;
using t = chrono::time_point<chrono::system_clock, chrono::duration<int, std::nano>>;
using c = chrono::high_resolution_clock;

void printTime(t start, string message);
int main() {
    t start;
    PointlessMap<char> map;
    map.insert(5, 'A');
    map.insert(10, 'B');
    map.insert(13, 'C');
    map.insert(6, 'D');
    map.insert(3, 'E');
    map.insert(15, 'F');
    map.insert(1, 'G');
    map.insert(8, 'H');

    short i = map.getFirstIndex();
    while(i < map.getLastIndex()){
        cout << i <<endl;
        i = map.getNext(i);
    }
    cout << i <<endl;



//    FileInputReader io("../data/ALDA practicum 1 - events_small.txt");
//    while(io.hasNext()){
//        FileInputReader::Entry line = io.nextLine();
//        cout << line.username << ", " << line.event.getDescription() << ", " << line.event.getTimeSpan().getDuration() << endl;
//    }

    // *****************************
    // Simplistic Agenda "Test"-code
    // *****************************
//    SimplisticAgenda simplisticAgenda;
//    SimplisticAgendaCLI simplisticAgendaCli{&simplisticAgenda};
//    simplisticAgenda.loadFromFile("../data/ALDA practicum 1 - events.txt");
//    printTime(start, "simplisticAgenda load bigfile");
//    simplisticAgendaCli.getInput();
//    simplisticAgendaCli.getInput();

    // *****************************
    // Advanced Agenda "Test"-code
    // *****************************
//    AdvancedAgenda advancedAgenda;
//    AdvancedAgendaCLI advancedAgendaCLI{&advancedAgenda};
//    advancedAgenda.loadFromFile("../data/ALDA practicum 1 - events.txt");
//
//    // add event
//    advancedAgendaCLI.addEvent();
//
//    // print all events from person
//    advancedAgendaCLI.askUser();
//
//    // update an event
//    advancedAgendaCLI.updateEvent();
//    advancedAgendaCLI.askUser();

//    Event e1({{30,22,19,10,2024}, 150}, "e1");
//    Event e2({{0,13,19,10,2024}, 60}, "e2");
//    Event e3({{30,13,19,10,2024}, 60}, "overlap met e2");
//    Event e4({{30,13,20,10,2024}, 60}, "zelfde uur als overlap met e2, maar andere dag");
//
//    Scheduler scheduler;
//    const bool schedularTest =
//            scheduler.plan({"Ebbe", "Robin", "Mathias"}, e1)
//            and scheduler.plan({"Ebbe", "Mathias"},e2)
//            and not scheduler.plan({"Ebbe", "Robin"},e3)
//            and scheduler.plan({"Ebbe", "Robin"},e4)
//            and scheduler.plan({"Robin"},e3);
//    if(!schedularTest) cerr << "schedularTest FAIL" << endl;
//
//    start = c::now();
//    scheduler.loadFromFile("../data/ALDA practicum 1 - events.txt");
//    printTime(start, "scheaduler load bigfile");
//
//    start = c::now();
//    FileInputReader file("../data/ALDA practicum 1 - events.txt");
//    while(file.hasNext()){
//        FileInputReader::Entry line = file.nextLine();
//        string name = line.username;
//        Event e = line.event;
//        //letterlijk niks doen
//    }
//    printTime(start, "load bigfile do nothing");

    return 0;
}
void printTime(t start, string message){
    t stop = c::now();
    d time = stop - start;
    cout << message << ": " << time.count() << " milliseconds" << endl;
}