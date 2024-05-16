
/* ==============================================
    Practicum 3 BESC:
    Team 12
        - Ebbe Wertz
        - Mathias Houwen
   ============================================== */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data.h"
#include "movieList.h"
#include "actorList.h"
#include "helper.h"

#define EXAMPLE_MOVIES_ACTORS_AMOUNT 7
#define EXAMPLE_MAX_MOVIES_PER_ACTOR 3


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

