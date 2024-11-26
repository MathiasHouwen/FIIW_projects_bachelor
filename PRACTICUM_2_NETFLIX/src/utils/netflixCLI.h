//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIXCLI_H
#define PRACTICUM_2_NETFLIX_NETFLIXCLI_H

#include <string>
#include "../modules/CLI.h"
#include "../Netflix.h"


using namespace std;


class netflixCLI {
public:
    bool getInput();
    const int displayNumber = 10;

private:
    CLI cli;
    Netflix netflix{};

    string prompt = "Enter parameters (end with '#' for partial matches): ";
    set<string> allowedParams = {"-type", "-t", "-g", "-y"};
    set<std::string> allowedFlags;

    void logic(CLI::Command cmd);
    void search(CLI::Command cmd);

    void printMos(vector<MovieOrShow> mosList, int maxNum);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIXCLI_H
