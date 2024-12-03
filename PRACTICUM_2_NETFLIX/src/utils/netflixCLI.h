// volledig door mathias
// doel: netflix-specifieke wrapper rond CLI

#ifndef PRACTICUM_2_NETFLIX_NETFLIXCLI_H
#define PRACTICUM_2_NETFLIX_NETFLIXCLI_H

#include <string>
#include <unordered_set>
#include "../modules/CLI.h"
#include "../Netflix.h"


using namespace std;


class netflixCLI {
public:
    /**
     * @brief idem aan CLI::getInput
     * @return commando
     * @Author Mathais
     */
    bool getInput();
    /**
     * @brief aantal entries die geprint moeten worden
     * @author Mathais
     */
    const int displayNumber = 10;

    explicit netflixCLI(const Netflix &netflix);

private:
    CLI cli;
    Netflix netflix;

    string prompt = "Enter parameters (end with '#' for partial matches): \n"
                    "'-type': 'movie' or 'show'\n"
                    "'-t': title, '-g':genre, '-y': releaseyear";
    unordered_set<string> allowedParams = {"-type", "-t", "-g", "-y"};
    unordered_set<string> allowedFlags;

    void logic(CLI::Command cmd);
    void search(CLI::Command cmd);

    void printMos(const vector<MovieOrShow*>& mosList, int maxNum);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIXCLI_H
