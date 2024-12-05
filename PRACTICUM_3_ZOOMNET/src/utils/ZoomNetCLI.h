//
// Created by houwe on 5/12/2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H
#define PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "../modules/CLI.h"
#include "../ZoomNet.h"

using namespace std;
class ZoomNetCLI {
public:
    void getInput();

    explicit ZoomNetCLI(const ZoomNet &model);

private:
    CLI cli;
    ZoomNet model;

    void design(unordered_map<string, string> params, unordered_set<string> flags);
    static void adapt(unordered_map<string, string> params, unordered_set<string> flags);
    static void optimize(unordered_map<string, string> params, unordered_set<string> flags);
    static void maintain(unordered_map<string, string> params, unordered_set<string> flags);

};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H