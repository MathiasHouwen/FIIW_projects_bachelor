//
// Created by ebbew on 17-10-2024.
//

#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEIO_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEIO_H


#include <string>
#include <fstream>
#include <ostream>
#include "charedClasses/Event.h"

class FileIO {
private:
    std::ifstream file;
public:
    struct Entry{
        std::string username;
        Event event;
    };
    Entry nextLine();
    FileIO(std::string fileName);
    ~FileIO();
    void closeFile();
    bool hasNext();
};


#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_FILEIO_H
