//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIXCLI_H
#define PRACTICUM_2_NETFLIX_NETFLIXCLI_H

#include <string>
#include "../modules/CLI.h"


using namespace std;


class netflixCLI {
public:
    bool getInput();
private:
    CLI cli;

    string prompt = "Enter parameters (end with '#' for partial matches): ";
    set<string> allowedParams = {"-type", "-t", "-g", "-y"};
    set<std::string> allowedFlags;

    void logic(CLI::Command cmd);

    void search(CLI::Command cmd);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIXCLI_H
