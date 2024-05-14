
/* ==============================================
    Practicum 3 BESC:
    Team 12
        - Ebbe Wertz
        - Mathias Houwen
   ============================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data.h"
#include "movieList.h"
#include "actorList.h"

#define EXAMPLE_MOVIES_ACTORS_AMOUNT 7
#define EXAMPLE_MAX_MOVIES_PER_ACTOR 3
#define NUMBERS_IN_ALPHABHET 26


//search
void searchMovies(char startChar, MovieNode* headIn, MovieNode** headFilteredOut);
void searchActors(char startChar, ActorNode* headIn, ActorNode** headFilteredOut);
void searchCoactorSingleMovie(MovieData* movieData, ActorData* actorData, ActorNode** coActorsHead);
void searchCoactor(MovieNode* movieHead, ActorData* actorData, ActorNode** coActorsHead);
bool containsActor(ActorNode* actorHead, ActorData* actorData);
//build index
void buildIndex(MovieNode* movieHead, MovieNode* index[NUMBERS_IN_ALPHABHET]);
//printers / extra
void printMallocErr(const char* type, const char* name);
void freeAll(MovieNode** movieHead, ActorNode** actorHead);

/*  =========================================================================
    ==       MAIN                                                          ==
    =========================================================================*/

int main() {
    MovieData movieDatas[EXAMPLE_MOVIES_ACTORS_AMOUNT] = {
            newMovie("B Movie 0", 1995),
            newMovie("A Movie 1", 1996),
            newMovie("C Movie 2", 1997),
            newMovie("B Movie 3", 1998),
            newMovie("C Movie 4", 1999),
            newMovie("Dubbel movie", 2000),
            newMovie("Dubbel movie", 2001)
    };
    ActorData actorDatas[EXAMPLE_MOVIES_ACTORS_AMOUNT] = {
            newActor("A Actor 0"),
            newActor("C Actor 1"),
            newActor("B Actor 2"),
            newActor("B Actor 3"),
            newActor("C Actor 4"),
            newActor("A Actor 5"),
            newActor("B Actor 6")
    };
    int actorsPerMovie[EXAMPLE_MOVIES_ACTORS_AMOUNT][EXAMPLE_MAX_MOVIES_PER_ACTOR] = {
            {6, 5, 2},
            {0, 1, 3},
            {4, 0,-1},
            {1,-1,-1},
            {2, 3,-1},
            {3, 4, 0},
            {5, 6,-1},
    };// -1 = geen actor. Dan hoef niet elke movie exact 3 actors

    MovieNode* movieHead = NULL;
    ActorNode* actorHead = NULL;

    for (int i = 0; i < EXAMPLE_MOVIES_ACTORS_AMOUNT; i++) {
        createOrInsertMovie(&movieHead, newMovieNode(&movieDatas[i]));
        createOrInsertActor(&actorHead, newActorNode(&actorDatas[i]));
        for (int j = 0; j < EXAMPLE_MAX_MOVIES_PER_ACTOR; j++) {
            int actorIndex = actorsPerMovie[i][j];
            if (actorIndex != -1) {
                addActorToMovie(&movieDatas[i], &actorDatas[actorIndex]);
            }
        }
    }

    MovieNode* index[NUMBERS_IN_ALPHABHET];
    MovieNode* filteredMovieHead = NULL;
    ActorNode* filteredActorsHead = NULL;
    ActorNode* coActorsHead = NULL;

    buildIndex(movieHead, index);

    searchMovies('B', movieHead, &filteredMovieHead);
    searchActors('A', actorHead, &filteredActorsHead);

    searchCoactor(movieHead, &actorDatas[2], &coActorsHead);

    deleteMovie(&movieHead, &movieDatas[3]);

    deleteActor(&movieHead, &actorHead, &actorDatas[2]);

    freeAll(&movieHead, &actorHead);

    return 0;
}
/*  =========================================================================
    ==       Helpers                                                       ==
    =========================================================================*/

void printMallocErr(const char* type, const char* name) {
    printf("\033[31m[ERROR] Geheugen kon niet worden toegewezen voor de nieuwe %s: '%s'\033[0m\n", type, name);
}

/*  =========================================================================
    ==       Search                                                        ==
    =========================================================================*/

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
//maakt list met actos met beginletter startChar
void searchActors(char startChar, ActorNode* headIn, ActorNode** headFilteredOut) {
    if (!headIn) {
        return; //na de call van Tail->next zal deze NULL zijn en kan recursie stoppen
    }
    ActorData* actorData = headIn->actor;
    const char* name = actorData->name;
    if (name[0] == startChar) {
        createOrInsertActor(headFilteredOut, newActorNode(actorData));
    }
    //ga recursief verder
    searchActors(startChar, headIn->next, headFilteredOut);
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
//boolean of een actors lijst een actor bevat
bool containsActor(ActorNode* actorHead, ActorData* actorData) {
    if (!actorHead) return false;
    if (actorHead->actor == actorData) return true;
    return containsActor(actorHead->next, actorData);
}

/*  =========================================================================
    ==       buildIndex                                                    ==
    =========================================================================*/

    //maakt de index array
void buildIndex(MovieNode* movieHead, MovieNode* index[NUMBERS_IN_ALPHABHET]) {
    memset(index, 0, sizeof(MovieNode) * NUMBERS_IN_ALPHABHET);
    //de buitenste loop voor films, binnenste voor index.
    //er kunnen makkelijk meer dan 26 films zijn en voor elke
    //index die geen film heeft, zou anders de hele movies list bekeken moeten worden
    //dit is dus sneller
    MovieNode* current = movieHead;
    while (current) {
        const char* name = current->movie->name;
        char fistChar = name[0];
        //char kan ge-interpreteerd worden als een integer. Deze hebben al een alfabetische volgorde
        int indexPos_A = fistChar - 'A';
        int indexPos_a = fistChar - 'a';
        //kleine letters komen na grote. Als 'a'-afstand negatief is, is het dus een grote letter
        int indexPos = indexPos_a < 0 ? indexPos_A : indexPos_a;
        //als nog niet in index, dan toevoegen
        if (!index[indexPos]) {
            index[indexPos] = current;
        }
        current = current->next;
    }
}

//verwijdert en free't alles
void freeAll(MovieNode** movieHead, ActorNode** actorHead) {
    ActorNode* currentActor = *actorHead;
    MovieNode* currentMovie = *movieHead;
    while (currentMovie) {
        deleteMovie(movieHead, currentMovie->movie);
        currentMovie = currentMovie->next;
    }
    while (currentActor) {
        deleteActor(movieHead, actorHead, currentActor->actor);
        currentActor = currentActor->next;
    }
}
