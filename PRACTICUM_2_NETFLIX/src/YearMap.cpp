//
// Created by houwe on 20/11/2024.
//

#include "YearMap.h"

using namespace std;

void YearMap::insert(MovieOrShow* mos, int releaseYear) {
    map[releaseYear]->insert(mos);
}

void YearMap::remove(MovieOrShow* mos) {
    for(auto entry : map){
        mosSet* set = entry.second;
        set->erase(mos);
    }
}

vector<MovieOrShow*> YearMap::search(int releaseYear, int numberOfElements) {
    vector<MovieOrShow*> result{};
    int count = 0;
    for(const auto& mos : *map[releaseYear]){
        if(count < numberOfElements) result.push_back(mos);
        count++;
    }
    return result;
}