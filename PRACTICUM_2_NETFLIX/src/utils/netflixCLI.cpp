//
// Created by houwe on 18/11/2024.
//

#include <iostream>
#include "../modules/CLI.h"
#include "netflixCLI.h"


bool netflixCLI::getInput() {

    try {
        CLI::Command cmd = cli.getInput(prompt);

        if (!cli.validate(cmd, allowedParams, allowedFlags)) {
            cout << "Command validation gefaald.\n";
            return false;
        }

        // TODO: CLI LOGIC

    } catch (const std::exception& e){
        cout << "Error: " << e.what() << "\n";
        return false;
    }

    return true;
}
