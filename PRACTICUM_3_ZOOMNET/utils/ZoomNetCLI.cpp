//
// Created by houwe on 5/12/2024.
//

#include "ZoomNetCLI.h"
#include "../modules/CLI.h"


void design(unordered_map<string, string> params, unordered_set<string> flags) {

}

void adapt(unordered_map<string, string> params, unordered_set<string> flags) {

}

void optimize(unordered_map<string, string> params, unordered_set<string> flags) {

}

void maintain(unordered_map<string, string> params, unordered_set<string> flags) {

}

ZoomNetCLI::ZoomNetCLI() {
    CLI cli({}, {});
    cli.registerCommand("design", &design, {}, {});
    cli.registerCommand("adapt", &adapt, {}, {});
    cli.registerCommand("optimize", &optimize, {}, {});
    cli.registerCommand("maintain", &maintain, {}, {});
}