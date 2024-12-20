// taakverdeling en uitleg: zie h-file

#include "ZoomNetCLI.h"

ZoomNetCLI::ZoomNetCLI(const ZoomNet &model) : cli({"-g", "-city1", "-city2", "-w"}, {"--all"}), model(model) {

    cli.registerCommand("adapt",
                        [this](unordered_map<string, string> params, unordered_set<string> flags) {
                                                this->adapt(params, flags);},
                        {"-g"}, {});

    cli.registerCommand("optimize",
                        [this](unordered_map<string, string> params, unordered_set<string> flags) {
                                                this->optimize(params, flags);},
                        {"-g", "-city1", "-city2", "-w"}, {});

    cli.registerCommand("maintain", [this](unordered_map<string, string> params, unordered_set<string> flags) {
                                                this->maintain(params, flags);},
                        {"-g"}, {"--all"});

    cli.registerCommand("design",
                        [this](unordered_map<string, string> params, unordered_set<string> flags) {
                            this->design(params, flags);},
                        {"-g"}, {});
}

// desgin -g [graphname]
void ZoomNetCLI::design(unordered_map<string, string> params, unordered_set<string> flags) {
    if (params.find("-g") != params.end()) {
        string graphName = params["-g"];

        model.designMST(graphName);
    } else {
        cerr << "Error: Graph name (-g) is required for the 'design' command." << endl;
    }
}

// adapt -g [graphname]
void ZoomNetCLI::adapt(unordered_map<string, string> params, unordered_set<string> flags) {
    if (params.find("-g") != params.end()) {
        string graphName = params["-g"];

        model.adaptMST(graphName);
    } else {
        cerr << "Error: Graph name (-g) is required for the 'adapt' command." << endl;
    }
}

// optimize -g [graphname] -city1 [stad 1] -city 2 [stad 2] -w [gewicht]
void ZoomNetCLI::optimize(unordered_map<string, string> params, unordered_set<string> flags) {
    string graphName{};
    string city1{};
    string city2{};
    string w{};
    int w_int;

    if (params.find("-g") != params.end()) {
        graphName = params["-g"];
    } else {
        cerr << "Error: Graph name (-g) is required for the 'design' command." << endl;
        return;
    }

    if (params.find("-city1") != params.end()) {
        city1 = params["-city1"];
    } else {
        cerr << "Error: -city1 is missing" << endl;
        return;
    }

    if (params.find("-city2") != params.end()) {
        city2 = params["-city2"];
    } else {
        cerr << "Error: city2 is missing." << endl;
        return;
    }

    if (params.find("-w") != params.end()) {
        w = params["-w"];
        w_int = stoi(w);
    } else {
        cerr << "Error: -w is aan het missen." << endl;
        return;
    }

    model.newConnectionBetter(graphName, city1, city2, w_int);
}

// maintain -g [graphname] --all (voeg flag toe als graphColouring)
void ZoomNetCLI::maintain(unordered_map<string, string> params, unordered_set<string> flags) {
    if (params.find("-g") != params.end()) {
        string graphName = params["-g"];

        if(flags.find("--all") != flags.end()){
            model.colourGraph(graphName);
            return;
        }

        model.generateChannels(graphName);
    } else {
        cerr << "Error: Graph name (-g) is required for the 'design' command." << endl;
    }
}

void ZoomNetCLI::getInput() {
    cli.getInput();
}
