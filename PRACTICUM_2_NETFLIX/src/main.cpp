//
// Created by robin on 18/11/2024.
//

#include "Netflix.h"
#include "utils/CSVHandler.h"

int main() {
    Netflix netflix;
    CSVHandler csv_handler(&netflix);
    csv_handler.handleCSV(std::string(DATA_PATH)+"/netflixdata_zonder_null.csv");

    return 0;
}
