//
// Created by houwe on 5/12/2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H
#define PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;
class ZoomNetCLI {
public:
    ZoomNetCLI();
private:
    static void design(unordered_map<string, string> params, unordered_set<string> flags);
    static void adapt(unordered_map<string, string> params, unordered_set<string> flags);
    static void optimize(unordered_map<string, string> params, unordered_set<string> flags);
    static void maintain(unordered_map<string, string> params, unordered_set<string> flags);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNETCLI_H