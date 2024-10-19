//
// Created by ebbew on 17-10-2024.
//

#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEINPUTREADER_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEINPUTREADER_H


#include <string>
#include <fstream>
#include <ostream>
#include "../event_classes/Event.h"

class FileInputReader {
private:
    std::ifstream file;
public:
    struct Entry{
        std::string username;
        Event event;
    };
    Entry nextLine();
    FileInputReader(std::string fileName);
    ~FileInputReader();
    void closeFile();
    bool hasNext();
};


#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEINPUTREADER_H
