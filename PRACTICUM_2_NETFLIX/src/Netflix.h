//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIX_H
#define PRACTICUM_2_NETFLIX_NETFLIX_H


#include "Trie.h"
#include "YearMap.h"
#include "StringPool.h"

using namespace std;

enum class Type{MOVIE, SHOW};

class Netflix {
private:
    Trie moviesTrie;
    Trie showsTrie;
    YearMap moviesYearMap;
    YearMap showsYearMap;
    StringPool genresPool;
public:
    void insert(Type type, string title, string genre, float IMDbRating, int releaseYear);
    void remove(Type type, string title, string genre);
    vector<MovieOrShow> searchByTitle(Type type, string title, string genre = "");
    vector<MovieOrShow> searchByReleaseYear(Type type, int releaseYear);
};


#endif //PRACTICUM_2_NETFLIX_NETFLIX_H
