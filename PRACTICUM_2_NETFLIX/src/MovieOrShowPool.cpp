// taakverdeling + functies documentatie: zie h-file

#include "MovieOrShowPool.h"

using namespace std;

MovieOrShow *MovieOrShowPool::use(const string &title, const string &genre, const float IMDbRating) {
    string* genrePtr = genresPool.use(genre, genre);
    return pool.use({title, genrePtr, IMDbRating}, genre + "___" +title);
}

void MovieOrShowPool::unuse(const string &title, const string &genre) {
    genresPool.unuse(genre);
    pool.unuse(genre + "___" +title);
}

MovieOrShow *MovieOrShowPool::peek(const string &title, const string &genre) const {
    return pool.peek(genre + "___" +title);
}

MovieOrShowPool::MovieOrShowPool() : pool(), genresPool(){
}

