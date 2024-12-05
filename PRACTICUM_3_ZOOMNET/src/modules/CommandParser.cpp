#include <iostream>
#include <sstream>
#include <unordered_set>
#include "CommandParser.h"

CommandParser::Command CommandParser::getInput(const string &prompt) {
    Command cmd;
    string inputLine;
    cout << prompt;
    getline(cin, inputLine);

    istringstream iss(inputLine);
    string word;

    // Het eerste woord in de string stream wordt het command
    if (iss >> word) {
        cmd.commandName = word;
    } else {
        throw runtime_error("Geen command");
    }

    parseToken(iss, cmd);

    return cmd;
}

void CommandParser::parseToken(istringstream& iss, CommandParser::Command& cmd){
    string word;
    if (!(iss >> word)) {
        return;
    }

    if (word.rfind("--", 0) == 0) {
        cmd.flags.insert(word);
    } else if (word.rfind('-', 0) == 0){
        string param = word;

        if (!(iss >> word)) {
            throw runtime_error("Parameter waarden mist voor " + param);
        }

        cmd.params[param] = word;
    } else {
        throw runtime_error("Invalid argument: " + word);
    }

    parseToken(iss, cmd);
}

bool CommandParser::validate(CommandParser::Command cmd, unordered_set<string> allowedParams, unordered_set<string> allowedFlags) {
    for(auto [param, value] : cmd.params){
        if (allowedParams.find(param) == allowedParams.end()) {
            return false;
        }
    }

    for ( auto flag : cmd.flags) {
        if (allowedFlags.find(flag) == allowedFlags.end()) {
            return false;
        }
    }

    return true;
}
