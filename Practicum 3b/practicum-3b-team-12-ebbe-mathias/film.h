#ifndef FILM_H
#define FILM_H

typedef struct MovieData MovieData;

struct MovieData {
    const char* name;
    int year;
    ActorNode* actors;
};

MovieData newMovie(const char* name, int year);
int compareMovies(void* movie1, void* movie2);

#endif