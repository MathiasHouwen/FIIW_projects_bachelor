cmake_minimum_required(VERSION 3.27.8)
project(alda_team3_ebbe_robin_mathias)

set(CMAKE_CXX_STANDARD 20)

add_executable(alda_team3_ebbe_robin_mathias main.cpp
        agenda/symplistic/SimpleAgenda.h
        agenda/symplistic/SimpleAgenda.cpp
        agenda/charedClasses/TimeSpan.h
        agenda/charedClasses/Event.h
        agenda/charedClasses/Event.cpp
        agenda/charedClasses/DateTime.h
        agenda/charedClasses/DateTime.cpp
        agenda/charedClasses/TimeSpan.cpp
        agenda/scheduler/Schedular.h
        agenda/scheduler/Schedular.cpp
        agenda/symplistic/SymplisticConsoleIO.h
        agenda/symplistic/SymplisticConsoleIO.cpp
        agenda/charedClasses/DateTime.h
        agenda/charedClasses/DateTime.h
        agenda/charedClasses/DateTime.cpp
        agenda/advanced/AdvancedAgenda.cpp
        agenda/advanced/advancedConsoleIO.h
        agenda/advanced/advancedConsoleIO.cpp
        agenda/FileIO.h
        agenda/FileIO.cpp
        agenda/ItervalTree.cpp
        agenda/ItervalTree.h)
