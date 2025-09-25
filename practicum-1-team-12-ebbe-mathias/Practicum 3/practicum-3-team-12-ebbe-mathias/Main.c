
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

#define EXAMPLE_MOVIES_ACTORS_AMOUNT 7
#define EXAMPLE_MAX_MOVIES_PER_ACTOR 3

typedef struct ActorData ActorData;
typedef struct ActorNode ActorNode;
typedef struct MovieData MovieData;
typedef struct MovieNode MovieNode;

struct ActorData {
    const char* name;
};

struct ActorNode {
    ActorData* actor;
    ActorNode* next;
    ActorNode* previous;
};

struct MovieData {
    const char* name;
    int year;
    ActorNode* actors;
};

struct MovieNode {
    MovieData* movie;
    MovieNode* next;
};

//constructors
MovieData newMovie(const char* name, int year);
ActorData newActor(const char* name);
MovieNode* newMovieNode(MovieData* movieData);
ActorNode* newActorNode(ActorData* actorData);
//compare
int compareMovies(void* movie1, void* movie2);
int compareActors(void* actor1, void* actor2);
//list builders
void insertMovie(MovieNode** head, MovieNode* movieNode);
void insertActor(ActorNode** head, ActorNode* actorNode);
void createOrInsertMovie(MovieNode** head, MovieNode* movieNode);
void createOrInsertActor(ActorNode** head, ActorNode* actorNode);
void addActorToMovie(MovieData* movieData, ActorData* actorData);
//delete
void deleteMovie(MovieNode** head, MovieData* movieData);
void deleteActor(MovieNode** movieHead, ActorNode** actorHead, ActorData* actorData);
void deleteActorFromActorList(ActorNode** head, ActorData* actorData);
void deleteActorFromMovie(MovieData* movieData, ActorData* actorData);
//search
void searchMovies(char startChar, MovieNode* headIn, MovieNode** headFilteredOut);
void searchActors(char startChar, ActorNode* headIn, ActorNode** headFilteredOut);
void searchCoactorSingleMovie(MovieData* movieData, ActorData* actorData, ActorNode** coActorsHead);
void searchCoactor(MovieNode* movieHead, ActorData* actorData, ActorNode** coActorsHead);
bool containsActor(ActorNode* actorHead, ActorData* actorData);
//build index
void buildIndex(MovieNode* movieHead, MovieNode* index[26]);
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

    for(int i=0; i<EXAMPLE_MOVIES_ACTORS_AMOUNT; i++){
        createOrInsertMovie(&movieHead, newMovieNode(&movieDatas[i]));
        createOrInsertActor(&actorHead, newActorNode(&actorDatas[i]));
        for(int j=0; j<EXAMPLE_MAX_MOVIES_PER_ACTOR; j++){
            int actorIndex = actorsPerMovie[i][j];
            if(actorIndex != -1){
                addActorToMovie(&movieDatas[i], &actorDatas[actorIndex]);
            }
        }
    }

    //Er zijn altijd 26 letters. Dat kan nooit veranderen dus 26 is hardcoded
    MovieNode * index[26];
    MovieNode* filteredMovieHead = NULL;
    ActorNode * filteredActorsHead = NULL;
    ActorNode * coActorsHead = NULL;

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

void printMallocErr(const char* type, const char* name){
    printf("\033[31m[ERROR] Geheugen kon niet worden toegewezen voor de nieuwe %s: '%s'\033[0m\n", type, name);
}

/*  =========================================================================
    ==       constructors                                                  ==
    =========================================================================*/

// Functie om een nieuwe movie struct te maken
MovieData newMovie(const char* name, int year) {
    MovieData movieData;
    movieData.name = name;
    movieData.year = year;
    movieData.actors = NULL; // leeg bij init, kan achteraf gevuld worden
    return movieData;
}

// Functie om een nieuwe acteur struct te maken
ActorData newActor(const char* name) {
    ActorData actorData;
    actorData.name = name;
    return actorData;
}

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

//maakt een nieuwe node van een actor
ActorNode* newActorNode(ActorData* actorData){
    //Geheugen alloceren op heap
    ActorNode* actorNode = malloc(sizeof(ActorNode));
    if (!actorNode) {
        printMallocErr("Actor", actorData->name);
        exit(EXIT_FAILURE);
    }
    //data
    actorNode->actor = actorData;
    actorNode->next = NULL;
    actorNode->previous = NULL;
    return actorNode;
}

/*  =========================================================================
    ==       Builders                                                      ==
    =========================================================================*/

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
    } else if (!current) {
        // Tail van de linkedlist
        prev->next = movieNode;
        movieNode->next = NULL;
    } else {
        // Middel van de linkedlist
        prev->next = movieNode;
        movieNode->next = current;
    }
}

//voegt een actor toe aan een bestaande linked list
void insertActor(ActorNode** head, ActorNode* actorNode){
    ActorNode* current = *head;
    ActorNode* prev = NULL;

    // Ga door de lijst tot bij de plaats waar die moet ge-insert worden
    while (current) {
        int compare = compareActors(actorNode->actor, current->actor);
        if(compare<0) break;
        //om een duplicate insert te negeren
        if(compare==0) return;
        prev = current;
        current = current->next;
    }

    if(!prev) {
        // HEAD
        actorNode->next = *head;
        (*head)->previous = actorNode;
        *head = actorNode;
    } else if (!current) {
        // TAIL
        prev->next = actorNode;
        actorNode->previous = prev;
    } else {
        prev->next = actorNode;
        actorNode->previous  = prev;
        actorNode->next = current;
        current->previous = actorNode;
    }
}

//voegt een movie toe een linked list, of initialiseert de list als ze nog niet bestaat
void createOrInsertMovie(MovieNode** head, MovieNode* movieNode){
    if(*head){
        insertMovie(head, movieNode);
    } else {
        *head = movieNode;
    }
}

//voegt een actor toe een linked list, of initialiseert de list als ze nog niet bestaat
void createOrInsertActor(ActorNode** head, ActorNode* actorNode){
    if(*head){
        insertActor(head, actorNode);
    } else {
        *head = actorNode;
    }
}

//voegt actor to aan de actors list van een movie
void addActorToMovie(MovieData* movieData, ActorData* actorData){
    createOrInsertActor(&(movieData->actors), newActorNode(actorData));
}

/*  =========================================================================
    ==       Compare                                                       ==
    =========================================================================*/

// return: > 0 Als movie1 eerder dan movie2
int compareMovies(void* movie1, void* movie2) {
    MovieData* movieData1 = (MovieData*)movie1;
    MovieData* movieData2 = (MovieData*)movie2;
    const int vergelijking = strcmp(movieData1->name, movieData2->name);
    // Guard clause: ongelijke naam = prioriteit
    if (vergelijking != 0) {
        return vergelijking;
    }

    return movieData1->year - movieData2->year;
}

int compareActors(void* actor1, void* actor2) {
    ActorData* actorData1 = (ActorData*)actor1;
    ActorData* actorData2 = (ActorData*)actor2;
    return strcmp(actorData1->name, actorData2->name);
}

/*  =========================================================================
    ==       Delete                                                        ==
    =========================================================================*/

//verwijderd movie (free ook de actors list van die movie)
void deleteMovie(MovieNode** head, MovieData* movieData){
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    while (current != NULL && compareMovies(movieData, current->movie) > 0) {
        prev = current;
        current = current->next;
    }

    //free actors list
    ActorNode* actorInMovie = movieData->actors;
    while(actorInMovie){
        deleteActorFromMovie(movieData, actorInMovie->actor);
        actorInMovie = actorInMovie->next;
    }

    if (!current) return; //movie zit niet in lijst
    if (!prev) {
        // Head van linkedlist
        *head = current->next;
    } else {
        // Middel van de linkedlist
        prev->next = current->next;
    }

    free(current);
}
//verwijderd een actor van een actors list
void deleteActorFromActorList(ActorNode** head, ActorData* actorData){
    ActorNode* current = *head;
    ActorNode* prev = NULL;

    while (current != NULL && compareActors(actorData, current->actor) > 0){
        prev = current;
        current = current->next;
    }

    if(!current) return; //actor zit niet in lijst
    if (!prev){
        //Head
        *head = current->next;
        ActorNode* next = current->next;
        //Een lijst van 1 lang kan head en tail zijn
        if(next){
            next->previous = NULL;
        }
    } else {
        //Mid
        ActorNode* next = current->next;
        prev->next = next;
        if(next){
            next->previous = prev;
        }
    }

    free(current);
}
//verwijderd actors van list en ook uit alle movies
void deleteActor(MovieNode** movieHead, ActorNode** actorHead, ActorData* actorData){
    MovieNode* currentMovie = *movieHead;
    while(currentMovie){
        //deleteActorFromActorList in deleteActorFromMovie negeert al actors die niet aanwezig zijn
        deleteActorFromMovie(currentMovie->movie, actorData);
        currentMovie = currentMovie->next;
    }
    deleteActorFromActorList(actorHead, actorData);
}
//verwijderd actor uit actors list van movie
void deleteActorFromMovie(MovieData* movieData, ActorData* actorData){
    deleteActorFromActorList(&(movieData->actors), actorData);
}


/*  =========================================================================
    ==       Search                                                        ==
    =========================================================================*/

//maakt list met movies met beginletter startChar
void searchMovies(char startChar, MovieNode* headIn, MovieNode** headFilteredOut){
    if(!headIn){
        return; //na de call van Tail->next zal deze NULL zijn en kan recursie stoppen
    }
    MovieData* movieData = headIn->movie;
    const char* name = movieData->name;
    if(name[0] == startChar){
        createOrInsertMovie(headFilteredOut, newMovieNode(movieData));
    }
    //ga recursief verder
    searchMovies(startChar, headIn->next, headFilteredOut);
}
//maakt list met actos met beginletter startChar
void searchActors(char startChar, ActorNode* headIn, ActorNode** headFilteredOut){
    if(!headIn){
        return; //na de call van Tail->next zal deze NULL zijn en kan recursie stoppen
    }
    ActorData* actorData = headIn->actor;
    const char* name = actorData->name;
    if(name[0] == startChar){
        createOrInsertActor(headFilteredOut, newActorNode(actorData));
    }
    //ga recursief verder
    searchActors(startChar, headIn->next, headFilteredOut);
}
//geeft alle andere actors coactors naast een gegeven actor in 1 movie
void searchCoactorSingleMovie(MovieData* movieData, ActorData* actorData, ActorNode** coActorsHead){
    ActorNode* actorNodeInMovie = movieData->actors;
    while(actorNodeInMovie){
        ActorData* actorDataInMovie = actorNodeInMovie->actor;
        //insert elke actor die niet deze actor is
        if(actorDataInMovie != actorData){
            //(inserActor negeert zelf al duplicaten)
            createOrInsertActor(coActorsHead, newActorNode(actorDataInMovie));
        }
        actorNodeInMovie = actorNodeInMovie->next;
    }
}
//zoekt coactors via alle movies
void searchCoactor(MovieNode* movieHead, ActorData* actorData, ActorNode** coActorsHead){
    if(!movieHead) return;
    MovieData* movieData = movieHead->movie;
    if(containsActor(movieData->actors, actorData)){
        searchCoactorSingleMovie(movieData, actorData, coActorsHead);
    }
    searchCoactor(movieHead->next, actorData, coActorsHead);
}
//boolean of een actors lijst een actor bevat
bool containsActor(ActorNode* actorHead, ActorData* actorData){
    if(!actorHead) return false;
    if(actorHead->actor == actorData) return true;
    return containsActor(actorHead->next, actorData);
}

/*  =========================================================================
    ==       buildIndex                                                    ==
    =========================================================================*/

//maakt de index array
void buildIndex(MovieNode* movieHead, MovieNode* index[26]){
    memset(index, 0, sizeof(MovieNode)*26);
    //de buitenste loop voor films, binnenste voor index.
    //er kunnen makkelijk meer dan 26 films zijn en voor elke
    //index die geen film heeft, zou anders de hele movies list bekeken moeten worden
    //dit is dus sneller
    MovieNode * current = movieHead;
    while(current){
        const char* name = current->movie->name;
        char fistChar = name[0];
        //char kan ge-interpreteerd worden als een integer. Deze hebben al een alfabetische volgorde
        int indexPos_A = fistChar-'A';
        int indexPos_a = fistChar-'a';
        //kleine letters komen na grote. Als 'a'-afstand negatief is, is het dus een grote letter
        int indexPos = indexPos_a < 0 ? indexPos_A : indexPos_a;
        //als nog niet in index, dan toevoegen
        if(!index[indexPos]){
            index[indexPos] = current;
        }
        current = current->next;
    }
}

//verwijdert en free't alles
void freeAll(MovieNode** movieHead, ActorNode** actorHead){
    ActorNode* currentActor = *actorHead;
    MovieNode* currentMovie = *movieHead;
    while(currentMovie){
        deleteMovie(movieHead, currentMovie->movie);
        currentMovie = currentMovie->next;
    }
    while(currentActor){
        deleteActor(movieHead, actorHead, currentActor->actor);
        currentActor = currentActor->next;
    }
}
