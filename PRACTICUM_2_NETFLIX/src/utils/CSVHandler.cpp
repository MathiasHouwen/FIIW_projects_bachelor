//
// Created by robin on 26/11/2024.
//

#include "CSVHandler.h"

#include <iostream>

using namespace std;

CSVHandler::CSVHandler(Netflix* netflix) {
    this->netflix = netflix;
}

void CSVHandler::handleCSV(const std::string &fileName) {
    csv::CSVReader reader(fileName);
    for (csv::CSVRow& row: reader) {

        string title = row["title"].get<string>();
        Type type = row["type"].get<string>() == "movie" ? Type::MOVIE : Type::SHOW;
        vector<string> genres = splitString(row["genres"].get<string>());
        int releaseYear = row["releaseYear"].get<int>();
        float IMDb = row["imdbAverageRating"].get<float>();
        //netflix->insert(type, row[0].get<>(), row[2].get<>(), row[4].get<float>(), row[3].get<int>());
    }
}

std::vector<std::string> CSVHandler::splitString(std::string str) {
    stringstream ss(str);
    vector<string> strings;
    string singleString;
    while (getline(ss, singleString, ',')) {
        if(singleString.starts_with(' '))
            singleString = singleString.substr(1, singleString.size() - 1);
        strings.push_back(singleString);
    }
    return strings;
}
