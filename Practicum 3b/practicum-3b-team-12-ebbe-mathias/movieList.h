#ifndef movieList_H
#define movieList_H

#include "data.h"
#include "actorList.h"

typedef struct MovieNode MovieNode;

struct MovieNode {
    MovieData* movie;
    MovieNode* next;
};

MovieNode* newMovieNode(MovieData* movieData);
void insertMovie(MovieNode** head, MovieNode* movieNode);
void createOrInsertMovie(MovieNode** head, MovieNode* movieNode);
void addActorToMovie(MovieData* movieData, ActorData* actorData);
void deleteMovie(MovieNode** head, MovieData* movieData);
void deleteActorFromMovie(MovieData* movieData, ActorData* actorData);

#endif