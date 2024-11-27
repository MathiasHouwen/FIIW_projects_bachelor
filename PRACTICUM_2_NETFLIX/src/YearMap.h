//
// Created by houwe on 20/11/2024.
//

#ifndef PRACTICUM_2_NETFLIX_YEARMAP_H
#define PRACTICUM_2_NETFLIX_YEARMAP_H

#include <unordered_map>
#include <set>
#include <vector>
#include "MovieOrShow.h"


class YearMap {
public:
    void insert(MovieOrShow* mos, int releaseYear);
    void remove(MovieOrShow* mos);
    std::vector<MovieOrShow*> search(int releaseYear, int numberOfElements);

private:
    using mosSet = std::unordered_set<MovieOrShow*>;
    std::unordered_map<int, mosSet*> map;
};


#endif //PRACTICUM_2_NETFLIX_YEARMAP_H
