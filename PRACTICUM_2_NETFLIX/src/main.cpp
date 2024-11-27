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

    auto movies = netflix.searchByReleaseYear(Type::MOVIE, 2010);
    for(auto movie : movies){
        std::cout << movie->toString() << std::endl;
    }
    std::cout << " -- " << std::endl;
    auto movies2 = netflix.searchByTitle(Type::MOVIE, "In", "Action");

    for(auto movie : movies2){
        std::cout << movie->toString() << std::endl;
    }

    //search -type movie -y 2010
    netflixCLI cli(netflix);
    cli.getInput();

    return 0;
}
