//
// Created by robin on 26/11/2024.
//

#include "CSVHandler.h"

#include <iostream>
using namespace std;

CSVHandler::CSVHandler(Netflix* netflix) {
    this->netflix = netflix;
}

void CSVHandler::handleCSV(const string &fileName) {
    CSVReader reader(fileName);
    Type type = {};
    for (CSVRow& row: reader) {
        if(row[1].get<>() == "movie") {
            type = Type::MOVIE;
            cout << "Movie:" << endl;
            for (auto && i : row) {
                cout << i.get<>();
            }
            cout << endl;
        }
        else if(row[1].get<>() == "tv") {
            type = Type::SHOW;
            cout << "Serie:" << endl;
            for (auto && i : row) {
                cout << i.get<>();
            }
            cout << endl;
        }
        netflix->insert(type, row[0].get<>(), row[2].get<>(), row[4].get<float>(), row[3].get<int>());
    }
}
