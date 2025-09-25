
#include <stdio.h>
#include <string.h>

#include "helper.h"

/*  =========================================================================
    ==       Helpers                                                       ==
    =========================================================================*/

void printMallocErr(const char* type, const char* name) {
    printf("\033[31m[ERROR] Geheugen kon niet worden toegewezen voor de nieuwe %s: '%s'\033[0m\n", type, name);
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