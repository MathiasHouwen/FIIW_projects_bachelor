// taakverdeling + functies documentatie: zie h-file

#include "MovieOrShowPool.h"

MovieOrShow *MovieOrShowPool::use(const MovieOrShow &mos) {
    genresPool.use(*mos.getGenre());
    return pool.use(mos);
}

void MovieOrShowPool::unuse(const MovieOrShow &mos) {
    genresPool.unuse(*mos.getGenre());
    pool.unuse(mos);
}

MovieOrShow *MovieOrShowPool::peek(const MovieOrShow &mos) {
    return pool.peek(mos);
}
