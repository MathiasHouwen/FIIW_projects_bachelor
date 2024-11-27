//
// Created by robin on 26/11/2024.
//

#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include "../Netflix.h"
#include "internal/csv_reader.hpp"

class CSVHandler {
private:
    Netflix* netflix;
public:
    explicit CSVHandler(Netflix* netflix);
    void handleCSV(const std::string& fileName);
};



#endif //CSVHANDLER_H
