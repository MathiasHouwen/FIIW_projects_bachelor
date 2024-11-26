//
// Created by robin on 26/11/2024.
//

#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include <fstream>
#include "../Netflix.h"
#include "internal/csv_reader.hpp"
using namespace std;
using namespace csv;

class CSVHandler {
private:
    Netflix* netflix;
public:
    explicit CSVHandler(Netflix* netflix);
    void handleCSV(const string& fileName);
};



#endif //CSVHANDLER_H
