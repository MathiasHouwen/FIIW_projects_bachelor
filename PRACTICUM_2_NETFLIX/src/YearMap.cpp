//
// Created by houwe on 20/11/2024.
//

#include "YearMap.h"

void YearMap::insert(MovieOrShow mos) {
    if(mos.getType() == MovieOrShow::Type::movie){
        return insert(mos, movieHash);
    }
    return insert(mos, serieHash);
}

void YearMap::insert(MovieOrShow mos, unordered_map<int, mosSet *> hashMap) {
    mosSet *set = hashMap[mos.getReleaseYear()];
    set->insert(mos);
}

void YearMap::remove(MovieOrShow mos) {
    if(mos.getType() == MovieOrShow::Type::movie){
        return remove(mos, movieHash);
    }
    return remove(mos, serieHash);
}

void YearMap::remove(MovieOrShow mos, unordered_map<int, mosSet *> hashMap) {
    mosSet *set = hashMap[mos.getReleaseYear()];
    set->erase(mos);
}

void YearMap::search(YearMap::mosSet::iterator it, YearMap::mosSet::iterator end, vector<MovieOrShow>& result, int remaining) {
    if (it == end || remaining == 0) {
        return;
    }
    result.push_back(*it);
    search(++it, end, result, remaining - 1);
}

vector<MovieOrShow> YearMap::search(int releaseYear, bool isMovie) {
    mosSet *set = isMovie ? movieHash[releaseYear] : serieHash[releaseYear];

    vector<MovieOrShow> result;
    if (set) {
        search(set->begin(), set->end(), result, 10);
    }

    return result;
}