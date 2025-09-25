// taakverdeling + functies documentatie: zie h-file

#include "MovieOrShowPool.h"

using namespace std;

MovieOrShow *MovieOrShowPool::use(const string &title, const StringSet &genres, const float IMDbRating, const string& id) {
    unordered_set<string*> genrePointers;
    for(const auto& genre : genres)
        genrePointers.insert(genresPool.use(genre, genre));
    return pool.use({title, genrePointers, IMDbRating, id}, id);
}

void MovieOrShowPool::unuse(const string& id) {
    MovieOrShow* mos = peek(id);
    for(auto genre : mos->getGenres())
        genresPool.unuse(*genre);
    pool.unuse(id);
}

MovieOrShow *MovieOrShowPool::peek(const string& id) const {
    return pool.peek(id);
}

MovieOrShowPool::MovieOrShowPool() : pool(), genresPool(){
}

std::string *MovieOrShowPool::peekGenre(const string &genre) const {
    return genresPool.peek(genre);
}

