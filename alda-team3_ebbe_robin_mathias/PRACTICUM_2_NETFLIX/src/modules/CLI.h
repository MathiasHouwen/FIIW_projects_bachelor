// volledig door mathias:
// Doel: CLI abstract maken voor hergebruik in meerdere practica

#ifndef PRACTICUM_2_NETFLIX_CLI_H
#define PRACTICUM_2_NETFLIX_CLI_H

#include <string>
#include <unordered_set>
#include <unordered_map>

class CLI {
public:
    using StringMap = std::unordered_map<std::string, std::string>;
    using StringSet = std::unordered_set<std::string>;
    ///@brief commando: heeft een naam, parameters (naam+value) en flags (enkel namen)
    struct Command{
        std::string commandName;
        StringMap params;
        StringSet flags;
    };

    /**
     * @brief vraagt om input en geeft dit terug in de vorm van een command struct
     * @param prompt: custom string om te displayen
     * @return: commando struct
     */
    Command getInput(const std::string &prompt);
    /**
     *
     * @param cmd: te valideren commando
     * @param allowedParams: toegelaten params
     * @param allowedFlags: toegelaten flags
     * @return: bool: correct/niet correct
     * @author Mathias
     */
    bool validate(Command cmd, StringSet allowedParams, StringSet allowedFlags);

private:
    void parseToken(std::istringstream& iss, CLI::Command& cmd);

};


#endif //PRACTICUM_2_NETFLIX_CLI_H