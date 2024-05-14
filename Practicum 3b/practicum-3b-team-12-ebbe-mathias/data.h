#ifndef DATA_H
#define DATA_H

#include "main.c"

typedef struct ActorData ActorData;
typedef struct MovieData MovieData;

struct ActorData {
    const char* name;
};

struct MovieData {
    const char* name;
    int year;
    ActorNode* actors;
};

MovieData newMovie(const char* name, int year);
ActorData newActor(const char* name);

int compareMovies(void* movie1, void* movie2);
int compareActors(void* actor1, void* actor2);

#endif