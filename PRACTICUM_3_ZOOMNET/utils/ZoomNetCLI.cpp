//
// Created by houwe on 5/12/2024.
//

#include "ZoomNetCLI.h"
#include "../modules/CLI.h"


ZoomNetCLI::ZoomNetCLI() {
    CLI cli({"-g"}, {});
    cli.registerCommand("design", &ZoomNetCLI::design, {"-g"}, {});
    cli.registerCommand("adapt", &ZoomNetCLI::adapt, {}, {});
    cli.registerCommand("optimize", &ZoomNetCLI::optimize, {}, {});
    cli.registerCommand("maintain", &ZoomNetCLI::maintain, {}, {});
}

// desgin -g [graphname]
void ZoomNetCLI::design(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::adapt(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::optimize(unordered_map<string, string> params, unordered_set<string> flags) {

}

void ZoomNetCLI::maintain(unordered_map<string, string> params, unordered_set<string> flags) {

}