//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIXCLI_H
#define PRACTICUM_2_NETFLIX_NETFLIXCLI_H

#include <string>
#include <unordered_set>
#include "../modules/CLI.h"
#include "../Netflix.h"

class netflixCLI {
public:
    bool getInput();
    const int displayNumber = 10;

private:
    CLI cli;
    Netflix netflix{};

    std::string prompt = "Enter parameters (end with '#' for partial matches): ";
    std::unordered_set<std::string> allowedParams = {"-type", "-t", "-g", "-y"};
    std::unordered_set<std::string> allowedFlags;

    void logic(CLI::Command cmd);
    void search(CLI::Command cmd);

    void printMos(const std::vector<MovieOrShow*>& mosList, int maxNum);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIXCLI_H
