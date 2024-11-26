//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIX_H
#define PRACTICUM_2_NETFLIX_NETFLIX_H


#include "Trie.h"
#include "YearMap.h"
#include "MovieOrShowPool.h"

using namespace std;

enum class Type{MOVIE, SHOW};

class Netflix {
private:
    Trie moviesTrie{};
    Trie showsTrie{};
    YearMap moviesYearMap{};
    YearMap showsYearMap{};
    MovieOrShowPool movieOrShowPool;
public:
    void insert(Type type, string title, string genre, float IMDbRating, int releaseYear);
    void remove(Type type, string title, string genre);
    vector<MovieOrShow*> searchByTitle(Type type, const string& title, const string& genre = "");
    vector<MovieOrShow*> searchByReleaseYear(Type type, int releaseYear);

    Netflix() = default;
};


#endif //PRACTICUM_2_NETFLIX_NETFLIX_H
