//
// Created by houwe on 18/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_CLI_H
#define PRACTICUM_2_NETFLIX_CLI_H

#include <string>
#include <unordered_set>
#include <unordered_map>

class CLI {
public:
    using StringMap = std::unordered_map<std::string, std::string>;
    using StringSet = std::unordered_set<std::string>;
    struct Command{
        std::string commandName;
        StringMap params;
        StringSet flags;
    };

    Command getInput(const std::string &prompt);
    bool validate(Command cmd, StringSet allowedParams, StringSet allowedFlags);

private:
    void parseToken(std::istringstream& iss, CLI::Command& cmd);

};


#endif //PRACTICUM_2_NETFLIX_CLI_H