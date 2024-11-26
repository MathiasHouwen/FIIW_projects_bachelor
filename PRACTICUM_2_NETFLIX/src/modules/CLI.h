//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_CLI_H
#define PRACTICUM_2_NETFLIX_CLI_H

#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class CLI {
public:
    struct Command{
        string commandName;
        unordered_map<string, string> params;
        unordered_set<string> flags;
    };

    Command getInput(const string &prompt);
    bool validate(Command cmd, unordered_set<string> allowedParams, unordered_set<string> allowedFlags);

private:
    void parseToken(istringstream& iss, CLI::Command& cmd);

};


#endif //PRACTICUM_2_NETFLIX_CLI_H