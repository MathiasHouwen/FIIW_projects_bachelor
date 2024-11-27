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
        unordered_set<string> genres = splitString(row["genres"].get<string>());
        int releaseYear = row["releaseYear"].get<int>();
        auto IMDb = row["imdbAverageRating"].get<float>();
        string id = row["imdbId"].get<string>();
        netflix->insert(type, title, genres, IMDb, releaseYear, id);
    }
}

std::unordered_set<std::string> CSVHandler::splitString(const std::string& str) {
    stringstream ss(str);
    unordered_set<string> strings;
    string singleString;
    while (getline(ss, singleString, ',')) {
        if(singleString.starts_with(' '))
            singleString = singleString.substr(1, singleString.size() - 1);
        strings.insert(singleString);
    }
    return strings;
}
