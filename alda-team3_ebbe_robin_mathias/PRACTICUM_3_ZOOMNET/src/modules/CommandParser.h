// Modules folder is klassen die we hergebruiken in meerdere practica.

// volledig door Mathias

// doel: parsen van een input string van CLI command formaat
// gebruikt voor de CLI class


#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class CommandParser {
public:
    struct Command{
        string commandName;
        unordered_map<string, string> params;
        unordered_set<string> flags;
    };

    Command getInput(const string &prompt);
    bool validate(Command cmd, unordered_set<string> allowedParams, unordered_set<string> allowedFlags);

private:
    void parseToken(istringstream& iss, CommandParser::Command& cmd);

};


#endif //COMMANDPARSER_H