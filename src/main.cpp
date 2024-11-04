#include <iostream>
#include <chrono>
#include "event_classes/Event.h"
#include "agenda_programmas/2_scheduler/Scheduler.h"
#include "util/FileInputReader.h"
#include "agenda_programmas/0_simplistic/SimplisticAgenda.h"
#include "agenda_programmas/0_simplistic/SimplisticAgendaCLI.h"
#include "agenda_programmas/1_advanced/AdvancedAgenda.h"
#include "agenda_programmas/1_advanced/AdvancedAgendaCLI.h"
#include "agenda_programmas/2_scheduler/SchedulerCLI.h"

using namespace std;
// voor timing testing (niet zo handig als O notatie maar toch wel interessant)
using d = chrono::duration<float, std::milli>;
using t = chrono::time_point<chrono::system_clock, chrono::duration<long long, std::nano>>;
using c = chrono::high_resolution_clock;

void printTime(t start, string message);
void testSimplistic();
void testAdvanced();
void testSchedular();
void measureFileRead();

int main() {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //TEST
    measureFileRead();
    testSimplistic();
    testAdvanced();
    testSchedular();
    cout<<endl<<" == START == "<<endl;
    SimplisticAgenda simplisticAgenda{};
    AdvancedAgenda advancedAgenda{};
    Scheduler scheduler{};
    simplisticAgenda.loadFromFile("../data/ALDA practicum 1 - events_small.txt");
    advancedAgenda.loadFromFile("../data/ALDA practicum 1 - events_small.txt");
    scheduler.loadFromFile("../data/ALDA practicum 1 - events_small.txt");

    char program;
    cout<<"Enter program: 'S'=simple agenda, 'A'=advanced agenda, 'C'=scheduler";
    cin >> program;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(program=='S'){
        SimplisticAgendaCLI cli{&simplisticAgenda};
        while (true){
            cli.getInput();
        }
    } else if(program=='A'){
        AdvancedAgendaCLI cli{&advancedAgenda};
        while (true){
            cli.getInput();
        }
    } else if(program=='C'){
        SchedulerCLI cli{&scheduler};
        while (true){
            cli.getInput();
        }
    }
    return 0;
}
void printTime(t start, string message){
    t stop = c::now();
    d time = stop - start;
    cout << message << ": " << time.count() << " milliseconds" << endl;
}

void testSimplistic(){
    // *****************************
    // Simplistic Agenda "Test"-code
    // *****************************
    SimplisticAgenda simplisticAgenda;
    SimplisticAgendaCLI simplisticAgendaCli{&simplisticAgenda};
    t start = c::now();
    simplisticAgenda.loadFromFile("../data/ALDA practicum 1 - events.txt");
    printTime(start, "simplisticAgenda load bigfile");
    //simplisticAgendaCli.getInput();
    //simplisticAgendaCli.getInput();
}
void testAdvanced(){
    // *****************************
    // Advanced Agenda "Test"-code
    // *****************************
    AdvancedAgenda advancedAgenda;
    AdvancedAgendaCLI advancedAgendaCLI{&advancedAgenda};
    t start = c::now();
    advancedAgenda.loadFromFile("../data/ALDA practicum 1 - events.txt");
    printTime(start, "advancedAgenda load bigfile");
    // add event
    //advancedAgendaCLI.addEvent();
    // print all events from person
    //advancedAgendaCLI.askUser();
    // update an event
    //advancedAgendaCLI.updateEvent();
    //advancedAgendaCLI.askUser();
}
void testSchedular(){
    t start;
    // *****************************
    // Schedular "Test"-code
    // *****************************
    Event e1({{30,22,19,10,2024}, 150}, "e1");
    Event e2({{0,13,19,10,2024}, 60}, "e2");
    Event e3({{30,13,19,10,2024}, 60}, "overlap met e2");
    Event e4({{30,13,20,10,2024}, 60}, "zelfde uur als overlap met e2, maar andere dag");
    Scheduler scheduler;
    const bool schedularTest =
            scheduler.plan({"Ebbe", "Robin", "Mathias"}, e1)
            and scheduler.plan({"Ebbe", "Mathias"},e2)
            and not scheduler.plan({"Ebbe", "Robin"},e3)
            and scheduler.plan({"Ebbe", "Robin"},e4)
            and scheduler.plan({"Robin"},e3);
    if(!schedularTest) cerr << "schedular simple test FAIL" << endl;
    else cout << "schedulartest simple test pass" <<endl;
    start = c::now();
    scheduler.loadFromFile("../data/ALDA practicum 1 - events.txt");
    printTime(start, "scheaduler load bigfile");
    start = c::now();
    scheduler.getSortedAgenda({"John Doe", "Jane Smith"});
    printTime(start, "scheaduler getsort 2 mensen");
}
void measureFileRead(){
    FileInputReader file("../data/ALDA practicum 1 - events.txt");
    t start = c::now();
    while(file.hasNext()){
        FileInputReader::Entry line = file.nextLine();
        string name = line.username;
        Event e = line.event;
        //letterlijk niks doen
    }
    printTime(start, "iterate bigfile do nothing");
}