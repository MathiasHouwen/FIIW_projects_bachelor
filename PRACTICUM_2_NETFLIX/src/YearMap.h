//
// Created by houwe on 20/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_YEARMAP_H
#define PRACTICUM_2_NETFLIX_YEARMAP_H

#include <unordered_map>
#include <set>
#include <vector>
#include "MovieOrShow.h"

using namespace std;

class YearMap {
public:
    using mosSet = set<MovieOrShow, MovieOrShow::mosComperator>;

    void insert(MovieOrShow mos);
    void remove(MovieOrShow mos);

    vector<MovieOrShow> search(int releaseYear, bool isMovie);

private:
    void insert(MovieOrShow mos, unordered_map<int, mosSet*> hashMap);
    void remove(MovieOrShow mos, unordered_map<int, mosSet*> hashMap);

    unordered_map<int, mosSet*> movieHash;
    unordered_map<int, mosSet*> serieHash;

    void search(mosSet::iterator it, mosSet::iterator end, vector<MovieOrShow> &result, int remaining);
};


#endif //PRACTICUM_2_NETFLIX_YEARMAP_H
