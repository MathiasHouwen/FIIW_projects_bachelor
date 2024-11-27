//
// Created by ebbew on 20-11-2024.
//

#include "Netflix.h"

using namespace std;

void Netflix::insert(Type type, string title, StringSet genres, float IMDbRating, int releaseYear, string id) {
    Trie& trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap& yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;

    MovieOrShow* mos = movieOrShowPool.use(title, genres, IMDbRating, id);

    trie.insertMOS(mos);
    yearMap.insert(mos, releaseYear);
}

void Netflix::remove(Type type, string id) {
    Trie& trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    YearMap& yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;

    MovieOrShow* mos = movieOrShowPool.peek(id);

    trie.deleteMOS(mos);
    yearMap.remove(mos);

    movieOrShowPool.unuse(id);
}

vector<MovieOrShow*> Netflix::searchByTitle(Type type, const string& partialTitle, const string& genre) {
    Trie& trie = type == Type::MOVIE ? moviesTrie : showsTrie;
    string* genrePointer = movieOrShowPool.peekGenre(genre);
    return trie.search(partialTitle, genrePointer);
}

vector<MovieOrShow*> Netflix::searchByReleaseYear(Type type, int releaseYear) {
    YearMap& yearMap = type == Type::MOVIE ? moviesYearMap : showsYearMap;
    return yearMap.search(releaseYear, 10);
}
