//
// Created by ebbew on 20-11-2024.
//

#include "Netflix.h"

using namespace std;

void Netflix::insert(Type type, string title, string genre, float IMDbRating, int releaseYear) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;

    MovieOrShow* mos = movieOrShowPool.use(title, genre, IMDbRating);

    trie.insertMOS(mos);
    yearMap.insert(mos, releaseYear);
}

void Netflix::remove(Type type, string title, string genre) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;

    MovieOrShow* mos = movieOrShowPool.peek(title, genre);

    trie.deleteMOS(mos);
    yearMap.remove(mos);

    movieOrShowPool.unuse(title, genre);
}

vector<MovieOrShow*> Netflix::searchByTitle(Type type, const string& partialTitle, const string& genre) {
    Trie trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    return trie.search(partialTitle, genre);
}

vector<MovieOrShow*> Netflix::searchByReleaseYear(Type type, int releaseYear) {
    YearMap yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;
    return yearMap.search(releaseYear, 10);
}
