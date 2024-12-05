//
// Created by houwe on 5/12/2024.
//

#include "ZoomNetCLI.h"

ZoomNetCLI::ZoomNetCLI(const ZoomNet &model) : cli({"-g"}, {}), model(model) {
    cli.registerCommand("design",
                        [this](unordered_map<string, string> params, unordered_set<string> flags) {
                                                this->design(params, flags);},
                        {"-g"}, {});
    cli.registerCommand("adapt", &ZoomNetCLI::adapt, {}, {});
    cli.registerCommand("optimize", &ZoomNetCLI::optimize, {}, {});
    cli.registerCommand("maintain", &ZoomNetCLI::maintain, {}, {});
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

void ZoomNetCLI::adapt(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::optimize(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::maintain(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::getInput() {
    cli.getInput();
}
