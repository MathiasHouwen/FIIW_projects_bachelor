// taakverdeling en uitleg: zie h-file

#include <iostream>
#include "CLI.h"

using namespace std;

bool CLI::getInput() {
    try {
        CommandParser::Command cmd = parser.getInput(prompt);

        if (commands.find(cmd.commandName) == commands.end()) {
            cout << "Unknown command: " << cmd.commandName << "\n";
            return false;
        }

        if (!parser.validate(cmd, allowedParams, allowedFlags)) {
            cout << "Command validation gefaald.\n";
            return false;
        }

        logic(cmd);

    } catch (const std::exception& e){
        cout << "Error: " << e.what() << "\n";
        return false;
    }

    return true;
}

void CLI::logic(CommandParser::Command cmd) {
    if (commands.find(cmd.commandName) != commands.end()) {
        commands[cmd.commandName](cmd.params, cmd.flags);
    }
}

void CLI::registerCommand(const string &name, function<void(unordered_map<string, string>, unordered_set<string>)> cmd,
                          const unordered_set<string> &params, const unordered_set<string> &flags) {

    commands[name] = [cmd, params, flags](unordered_map<string, string> funcParams,
                                          unordered_set<string> funcFlags){
        for (auto &key : params){
            funcParams.emplace(key, "");
        }
        funcFlags.insert(flags.begin(), flags.end());
        cmd(std::move(funcParams), std::move(funcFlags));
    };

}

CLI::CLI(const unordered_set<string> &allowedParams, const unordered_set<string> &allowedFlags) : allowedParams(
        allowedParams), allowedFlags(allowedFlags) {}