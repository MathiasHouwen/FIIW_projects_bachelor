//
// Created by robin on 26/11/2024.
//

#include "CSVHandler.h"

CSVHandler::CSVHandler(Netflix* netflix) {
    this->netflix = netflix;
}

void CSVHandler::handleCSV(const string &fileName) {
    CSVReader reader(fileName);
    Type type = {};
    for (CSVRow& row: reader) {
        if(row[1].get<string>() == "movie") {
            type = Type::MOVIE;
        }
        else if(row[1].get<string>() == "tv") {
            type = Type::SHOW;
        }
        netflix->insert(type, row[0].get<string>(), row[2].get<string>(), row[4].is_float(), row[3].is_float());
    }
}
