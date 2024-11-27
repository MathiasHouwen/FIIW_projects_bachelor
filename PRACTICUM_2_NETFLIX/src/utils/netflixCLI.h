//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIXCLI_H
#define PRACTICUM_2_NETFLIX_NETFLIXCLI_H

#include <string>
#include <unordered_set>
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
    unordered_set<string> allowedParams = {"-type", "-t", "-g", "-y", "-title"};
    unordered_set<string> allowedFlags;

    void logic(CLI::Command cmd);
    void search(CLI::Command cmd);

    void printMos(const vector<MovieOrShow*>& mosList, int maxNum);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIXCLI_H
