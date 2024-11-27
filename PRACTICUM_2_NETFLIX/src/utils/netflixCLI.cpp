//
// Created by houwe on 18/11/2024.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "../modules/CLI.h"
#include "netflixCLI.h"
#include "../MovieOrShow.h"

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
    if(!cmd.params.contains("-type")){
        cout << "first param 'type' is not found\n";
    }

    string stringType;
    Type type;
    stringType = cmd.params.at("-type");

    if (stringType == "movie") {
        type = Type::MOVIE;
    } else if (stringType == "show" || stringType == "serie") {
        type = Type::SHOW;
    } else {
        cout << "Error: Invalid 'type' value. Accepted values are 'movie' or 'show'.\n";
        return;
    }

    if(cmd.params.contains("-t")){

        if(!cmd.params.contains("-title")){
            cout << "Error: geen title of partial title\n";
            return;
        }

        string title = cmd.params["-title"];
        if(title.find('#') != std::string::npos && title.back() == '#'){
            // partial title
            title.pop_back();
        }

        if(cmd.params.contains("-g")){
            string genre = cmd.params["-g"];
            vector<MovieOrShow*> mos = netflix.searchByTitle(type, title, genre);
            printMos(mos, displayNumber);
            return;
        }

        vector<MovieOrShow*> mos = netflix.searchByTitle(type, title);
        printMos(mos, displayNumber);
        return;
    }

    if(cmd.params.contains("-y")){
        // Search by year
        string yearString = cmd.params["-y"];
        stringstream ss;
        ss << yearString;
        int year;
        ss >> year;
        vector<MovieOrShow*> mos = netflix.searchByReleaseYear(type, year);
        printMos(mos, displayNumber);
        return;
    }

    cout << "second param not found\n";
}

void netflixCLI::printMos(const vector<MovieOrShow*>& mosList, int maxNum) {
    int count = 0;
    for (const auto& mos : mosList) {
        if (count >= maxNum) break;
        std::cout << "(" << count << ") " << mos->toString() << std::endl;
        count++;
    }
}
