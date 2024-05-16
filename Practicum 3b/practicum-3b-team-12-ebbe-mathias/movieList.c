#include <stdio.h>
#include "movieList.h"

//maakt een nieuwe node van een movie
MovieNode* newMovieNode(MovieData* movieData) {
    //Geheugen alloceren op heap
    MovieNode* movieNode = malloc(sizeof(MovieNode));
    if (!movieNode) {
        printMallocErr("Movie", movieData->name);
        exit(EXIT_FAILURE);
    }
    //data
    movieNode->movie = movieData;
    movieNode->next = NULL;
    return movieNode;
}

//voegt een movie toe aan een bestaande linked list
void insertMovie(MovieNode** head, MovieNode* movieNode) {
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    // Ga door de lijst tot bij de plaats waar die moet ge-insert worden
    while (current && compareMovies(movieNode->movie, current->movie) > 0) {
        prev = current;
        current = current->next;
    }

    if (!prev) {
        // Head van linkedlist
        movieNode->next = *head;
        *head = movieNode;
    }
    else if (!current) {
        // Tail van de linkedlist
        prev->next = movieNode;
        movieNode->next = NULL;
    }
    else {
        // Middel van de linkedlist
        prev->next = movieNode;
        movieNode->next = current;
    }
}

//voegt een movie toe een linked list, of initialiseert de list als ze nog niet bestaat
void createOrInsertMovie(MovieNode** head, MovieNode* movieNode) {
    if (*head) {
        insertMovie(head, movieNode);
    }
    else {
        *head = movieNode;
    }
}

//voegt actor to aan de actors list van een movie
void addActorToMovie(MovieData* movieData, ActorData* actorData) {
    createOrInsertActor(&(movieData->actors), newActorNode(actorData));
}

//verwijderd movie (free ook de actors list van die movie)
void deleteMovie(MovieNode** head, MovieData* movieData) {
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    while (current != NULL && compareMovies(movieData, current->movie) > 0) {
        prev = current;
        current = current->next;
    }

    //free actors list
    ActorNode* actorInMovie = movieData->actors;
    while (actorInMovie) {
        deleteActorFromMovie(movieData, actorInMovie->actor);
        actorInMovie = actorInMovie->next;
    }

    if (!current) return; //movie zit niet in lijst
    if (!prev) {
        // Head van linkedlist
        *head = current->next;
    }
    else {
        // Middel van de linkedlist
        prev->next = current->next;
    }

    free(current);
}

//verwijderd actor uit actors list van movie
void deleteActorFromMovie(MovieData* movieData, ActorData* actorData) {
    deleteActorFromActorList(&(movieData->actors), actorData);
}

//maakt list met movies met beginletter startChar
void searchMovies(char startChar, MovieNode* headIn, MovieNode** headFilteredOut) {
    if (!headIn) {
        return; //na de call van Tail->next zal deze NULL zijn en kan recursie stoppen
    }
    MovieData* movieData = headIn->movie;
    const char* name = movieData->name;
    if (name[0] == startChar) {
        createOrInsertMovie(headFilteredOut, newMovieNode(movieData));
    }
    //ga recursief verder
    searchMovies(startChar, headIn->next, headFilteredOut);
}

//geeft alle andere actors coactors naast een gegeven actor in 1 movie
void searchCoactorSingleMovie(MovieData* movieData, ActorData* actorData, ActorNode** coActorsHead) {
    ActorNode* actorNodeInMovie = movieData->actors;
    while (actorNodeInMovie) {
        ActorData* actorDataInMovie = actorNodeInMovie->actor;
        //insert elke actor die niet deze actor is
        if (actorDataInMovie != actorData) {
            //(inserActor negeert zelf al duplicaten)
            createOrInsertActor(coActorsHead, newActorNode(actorDataInMovie));
        }
        actorNodeInMovie = actorNodeInMovie->next;
    }
}
//zoekt coactors via alle movies
void searchCoactor(MovieNode* movieHead, ActorData* actorData, ActorNode** coActorsHead) {
    if (!movieHead) return;
    MovieData* movieData = movieHead->movie;
    if (containsActor(movieData->actors, actorData)) {
        searchCoactorSingleMovie(movieData, actorData, coActorsHead);
    }
    searchCoactor(movieHead->next, actorData, coActorsHead);
}