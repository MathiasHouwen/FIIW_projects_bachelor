// taakverdeling + functies documentatie: zie h-file

#include "MovieOrShowPool.h"

MovieOrShow *MovieOrShowPool::use(const string &title, const string &genre, const float IMDbRating) {
    string* genrePtr = genresPool.use(genre);
    return pool.use({title, genrePtr, IMDbRating});
}

void MovieOrShowPool::unuse(const string &title, const string &genre) {
    genresPool.unuse(genre);
    pool.unuse({});
}

MovieOrShow *MovieOrShowPool::peek(const string &title, const string &genre) const {
    return pool.peek(mos);
}

