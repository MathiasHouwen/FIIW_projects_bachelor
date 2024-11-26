//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_NETFLIX_H
#define PRACTICUM_2_NETFLIX_NETFLIX_H


#include "Trie.h"
#include "YearMap.h"
#include "MovieOrShowPool.h"

enum class Type{MOVIE, SHOW};

class Netflix {
private:
    Trie moviesTrie{};
    Trie showsTrie{};
    YearMap moviesYearMap{};
    YearMap showsYearMap{};
    MovieOrShowPool movieOrShowPool;
public:
    void insert(Type type, std::string title, std::string genre, float IMDbRating, int releaseYear);
    void remove(Type type, std::string title, std::string genre);
    std::vector<MovieOrShow*> searchByTitle(Type type, const std::string& title, const std::string& genre = "");
    std::vector<MovieOrShow*> searchByReleaseYear(Type type, int releaseYear);

    Netflix() = default;
};


#endif //PRACTICUM_2_NETFLIX_NETFLIX_H
