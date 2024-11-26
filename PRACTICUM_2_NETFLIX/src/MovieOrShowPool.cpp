// taakverdeling + functies documentatie: zie h-file

#include "MovieOrShowPool.h"

MovieOrShow *MovieOrShowPool::use(const string &title, const string &genre, const float IMDbRating) {
    string* genrePtr = genresPool.use(genre);
    return pool.use({title, genrePtr, IMDbRating}, {genre, title});
}

void MovieOrShowPool::unuse(const string &title, const string &genre) {
    genresPool.unuse(genre);
    pool.unuse({genre, title});
}

MovieOrShow *MovieOrShowPool::peek(const string &title, const string &genre) const {
    return pool.peek({genre, title});
}

MovieOrShowPool::MovieOrShowPool() {
    pool = Pool<minimalUniqueMOSKey, MovieOrShow>();
    genresPool = Pool<string>();
}

