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

        logic(cmd);

    } catch (const std::exception& e){
        cout << "Error: " << e.what() << "\n";
        return false;
    }

    return true;
}

void netflixCLI::logic(CLI::Command cmd){
    // Dit maakt code uitbreidbaar
    if (cmd.commandName == "search") {
        // Logic for search
    }
    search(cmd);
}

void netflixCLI::search(CLI::Command cmd){
    if(!cmd.flags.contains("-type")){
        cout << "first param 'type' is not found\n";
    }

    if(cmd.flags.contains("-t")){
        // name trie logic or something funcky

        if(cmd.flags.contains("-g")){
            // Do funkey thins with both
            return;
        }
        return;
    }

    if(cmd.flags.contains("-y")){
        // Search by year
        return;
    }

    cout << "second param not found\n";
}