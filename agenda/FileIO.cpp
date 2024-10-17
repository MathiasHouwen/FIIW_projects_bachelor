//
// Created by ebbew on 17-10-2024.
//

#include <iostream>
#include <sstream>
#include "FileIO.h"

FileIO::FileIO(std::string fileName) {
    file.open(fileName);
    if(!file.is_open()){
        std::cerr << "Could not open file" << std::endl;
    }
}

FileIO::~FileIO() {
    closeFile();
}


void FileIO::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}
FileIO::Entry FileIO::nextLine() {
    std::string line;
    if (std::getline(file, line) && !line.empty()) {
        std::istringstream is(line);
        std::string userName, description;
        int year, month, day, hour, minute, duration;
        char d = ';'; // d = delimiter
        std::getline(is, userName, d);
        std::getline(is, description, d);
        is >> year >> d >> month >> d >> day >> d;
        is >> hour >> d >> minute >> d >> duration;
        Event event({{minute, hour, day, month, year}, duration}, description);
        return Entry(userName, event);
    }
    std::cerr << "no lines left to read" << std::endl;
}

bool FileIO::hasNext() {
    std::string line;
    return !file.eof() || (std::getline(file, line) && !line.empty());
}
