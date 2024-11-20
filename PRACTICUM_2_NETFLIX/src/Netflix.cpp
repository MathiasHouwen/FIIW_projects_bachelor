//
// Created by ebbew on 20-11-2024.
//

#include "Netflix.h"

void Netflix::insert(Type type, string title, string genre, float IMDbRating, int releaseYear) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;
    string* genrePointer = genresPool.use(genre);
    trie.insertMOS(new MovieOrShow(title, genrePointer, IMDbRating));
    yearMap.insert({title, genrePointer, IMDbRating}, releaseYear);
}

void Netflix::remove(Type type, string title, string genre) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;
    trie.deleteMOS(new MovieOrShow(title, &genre, 0));
    yearMap.remove({title, &genre, 0});
}

vector<MovieOrShow> Netflix::searchByTitle(Type type, string title, string genre) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    return trie.search(title, &genre);
}

vector<MovieOrShow> Netflix::searchByReleaseYear(Type type, int releaseYear) {
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;
    return yearMap.search(releaseYear, 10);
}
