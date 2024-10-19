cmake_minimum_required(VERSION 3.27.8)
project(alda_team3_ebbe_robin_mathias)

set(CMAKE_CXX_STANDARD 20)

add_executable(alda_team3_ebbe_robin_mathias src/main.cpp
        src/agenda_programmas/0_simplistic/SimplisticAgenda.h
        src/agenda_programmas/0_simplistic/SimplisticAgenda.cpp
        src/event_classes/TimeSpan.h
        src/event_classes/Event.h
        src/event_classes/Event.cpp
        src/event_classes/DateTime.h
        src/event_classes/DateTime.cpp
        src/event_classes/TimeSpan.cpp
        src/agenda_programmas/2_scheduler/Scheduler.h
        src/agenda_programmas/2_scheduler/Scheduler.cpp
        src/agenda_programmas/0_simplistic/SimplisticAgendaCLI.h
        src/agenda_programmas/0_simplistic/SimplisticAgendaCLI.cpp
        src/event_classes/DateTime.h
        src/event_classes/DateTime.h
        src/event_classes/DateTime.cpp
        src/agenda_programmas/1_advanced/AdvancedAgenda.cpp
        src/agenda_programmas/1_advanced/AdvancedAgendaCLI.h
        src/agenda_programmas/1_advanced/AdvancedAgendaCLI.cpp
        src/util/FileInputReader.h
        src/util/FileInputReader.cpp
        src/AgendaInterface.h
        src/agenda_programmas/2_scheduler/SchedulerCLI.cpp
        src/agenda_programmas/2_scheduler/SchedulerCLI.h
)
