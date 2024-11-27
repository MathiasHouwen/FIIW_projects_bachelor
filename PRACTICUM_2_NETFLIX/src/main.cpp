//
// Created by robin on 18/11/2024.
//

#include <iostream>
#include "Netflix.h"
#include "utils/CSVHandler.h"
#include "utils/netflixCLI.h"

int main() {
    Netflix netflix;
    CSVHandler csv_handler(&netflix);
    csv_handler.handleCSV(std::string(DATA_PATH)+"/netflixdata_zonder_null.csv");

    /*
     *  Commands moeten van het typen zijn,
     *  Command param value ....
     *  Bv,
     *  search -type movie -y 2010
     *  search -type movie -g Action -t In#
     */
    netflixCLI cli(netflix);
    cli.getInput();

    return 0;
}
