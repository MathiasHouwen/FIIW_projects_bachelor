#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int compareMovies(MovieData* movie1, MovieData* movie2);
int compareActors(ActorData* actor1, ActorData* actor2);
//insert
void insertMovie(MovieNode** head, MovieNode* movieNode);
void insertActor(ActorNode** head, ActorNode* actorNode);
void createOrInsertMovie(MovieNode** head, MovieNode* movieNode);
void createOrInsertActor(ActorNode** head, ActorNode* actorNode);
//delete
void deleteMovie(MovieNode** head, MovieNode* movieData);
void deleteActor(ActorNode** head, ActorNode* actorNode);
//search
void searchMovies(char startChar, MovieNode* headIn, MovieNode* headFilteredOut);
void searchActors(char startChar, ActorNode* headIn, ActorNode* headFilteredOut);
//extra helpers
void addActorToMovie(MovieNode* movieHead, ActorNode* actorNode);
void printMallocErr(const char* type, const char* name);


void movieTestCode();
void acteurTestCode();
void compareMoviesTestCode();
void insertMovieTestCode();
void insertActorTestCode();
void deleteMovieTestCode();

int main() {
    MovieData mov1 = newMovie("Mov1", 1);
    MovieData mov2 = newMovie("Mov2", 1);
    MovieData mov4 = newMovie("Mov4", 1);
    MovieData mov0 = newMovie("Mov0", 1);
    MovieData mov3 = newMovie("Mov3", 1);
    MovieNode* movieHead;

    createOrInsertMovie(&movieHead, newMovieNode(&mov1));
    createOrInsertMovie(&movieHead, newMovieNode(&mov2));
    createOrInsertMovie(&movieHead, newMovieNode(&mov4));
    createOrInsertMovie(&movieHead, newMovieNode(&mov0));
    createOrInsertMovie(&movieHead, newMovieNode(&mov3));
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
    ActorNode *current = *head;
    ActorNode *prev = NULL;

    // Ga door de lijst tot bij de plaats waar die moet ge-insert worden
    while (current && compareActors(actorNode->actor, current->actor) > 0){
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
    if(head){
        insertMovie(head, movieNode);
    } else {
        *head = movieNode;
    }
}

//voegt een actor toe een linked list, of initialiseert de list als ze nog niet bestaat
void createOrInsertActor(ActorNode** head, ActorNode* actorNode){
    if(head){
        insertActor(head, actorNode);
    } else {
        *head = actorNode;
    }
}

/*  =========================================================================
    ==       Compare                                                       ==
    =========================================================================*/

// return: >0 Als movie1 eerder dan movie2
int compareMovies(MovieData* movie1, MovieData* movie2) {
    int vergelijking = strcmp(movie1->name, movie2->name);

    // Als de naam niet gelijk is aan elkaar
    if (vergelijking != 0) {
        return vergelijking;
    }

    return movie1->year - movie2->year;
}

int compareActors(ActorData* actor1, ActorData* actor2) {
    return strcmp(actor1->name, actor2->name);
}


/*

void deleteActor(MovieNode* head, ActorData* acteur){
    // Als er nog geen acteurs bij de films zijn
    MovieData *mover = head->movie;
    if(mover->actors == NULL){
        printf("Movie heeft geen acteurs jonge.\n");
        return;
    }

    ActorNode *current = mover->actors;
    ActorNode *prev = NULL;

    while (current != NULL && compareActors(acteur, current->actor) > 0){
        // TRAVEL THRUE LIST
        prev = current;
        current = current->next;
    }

    if(current == NULL){
        // Tail van de linkedlist
        printf("Acteur bestaat niet jonge.\n");
        return;
    } else if (prev == NULL){
        mover->actors = current->next;
        current->next->previous = NULL;
    } else {
        prev->next = current->next;
        current->previous = prev;
    }

    free(acteur);
    free(current->actor);
    free(current);
}

// TODO: TEST
void addActorToMovie(MovieNode* movieHead, ActorNode* actorNode){
    // Als er nog geen acteurs bij de films zijn
    MovieData *mover = movieHead->movie;
    if(mover->actors == NULL){
        mover->actors = actorNode;
        return;
    }

    ActorNode *current = mover->actors;
    ActorNode *prev = NULL;

    while (current != NULL && compareActors(actorNode->actor, current->actor) > 0){
        // TRAVEL THRUE LIST
        prev = current;
        current = current->next;
    }

    if(prev == NULL) {
        // HEAD
        mover->actors = actorNode;
        current->previous = actorNode;
        actorNode->next = current;
    } else if (current == NULL) {
        // TAIL
        prev->next = actorNode;
        actorNode->previous = prev;
    } else {
        prev->next = actorNode;
        actorNode->next = current;
        actorNode->previous  = prev;
        current->previous = actorNode;
    }
}



void deleteMovie(MovieNode** head, MovieNode* movieData){
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    while (current != NULL && compareMovies(movieData, current->movie) > 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Tail van de linkedlist
        printf("Movie bestaat niet jonge.\n");
        return;
    } else if (prev == NULL) {
        // Head van linkedlist
        *head = current->next;
    } else {
        // Middel van de linkedlist
        prev->next = current->next;
    }

    free(movieData);
    free(current->movie);
    free(current);
}


void newOrInsertMovie(MovieNode** head, MovieNode* newNode){

}
void searchMovies(char startChar, MovieNode* headIn, MovieNode* headFilteredOut){
    if(!headIn){
        return;
    }
    const char* name = headIn->movie->name;
    if(name[0] == startChar){
        //add aan headFilteredOut
    }
    MovieNode* nextMovie = headIn->next;
    searchMovies(startChar, nextMovie, headFilteredOut)
}
void searchActors(char startChar, ActorNode* headIn, ActorNode* headFilteredOut){
}
*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/
/* =============================[TEST CODE]===========================================*/

/*
void movieTestCode() {
    MovieData* movie1 = newMovie("Inception", 2010);
    MovieData* movie2 = newMovie("The Shawshank Redemption", 1994);

    printf("Film 1: %s (%d)\n", movie1->name, movie1->year);
    printf("Film 2: %s (%d)\n", movie2->name, movie2->year);

    free(movie1);
    free(movie2);
}

void acteurTestCode() {
    ActorData* actor1 = newActor("Leonardo DiCaprio");
    ActorData* actor2 = newActor("Morgan Freeman");

    printf("Acteur 1: %s\n", actor1->name);
    printf("Acteur 2: %s\n", actor2->name);

    free(actor1);
    free(actor2);
}

void compareMoviesTestCode() {
    // Maak een array van films
    MovieData movies[] = {
        {"Inception", 2010},
        {"The Shawshank Redemption", 1994},
        {"Pulp Fiction", 1994},
        {"The Godfather", 1972},
        {"Forrest Gump", 1994}
    };

    // Sorteer de array van films
    //qsort(movies, sizeof(movies) / sizeof(movies[0]), sizeof(struct MovieData),
    //      (_CoreCrtNonSecureSearchSortCompareFunction) compareMovies);

    // Geef de gesorteerde films weer
    printf("Gesorteerde films:\n");
    for (int i = 0; i < sizeof(movies) / sizeof(movies[0]); i++) {
        printf("%s (%d)\n", movies[i].name, movies[i].year);
    }
}

void insertActorTestCode() {
    MovieData* movieData = newMovie("Pulp Fiction", 1994);
    MovieNode* movie = newMovieNode(movieData);

    ActorData* actor1 = newActor("Tom Hanks");
    ActorData* actor2 = newActor("Meryl Streep");
    ActorData* actor3 = newActor("Leonardo DiCaprio");
    ActorData* actor4 = newActor("Jennifer Lawrence");
    ActorData* actor5 = newActor("Brad Pitt");

    ActorNode* actorNode1 = newActorNode(actor1);
    ActorNode* actorNode2 = newActorNode(actor2);
    ActorNode* actorNode3 = newActorNode(actor3);
    ActorNode* actorNode4 = newActorNode(actor4);
    ActorNode* actorNode5 = newActorNode(actor5);

    addActorToMovie(movie, actorNode1);
    addActorToMovie(movie, actorNode2);
    addActorToMovie(movie, actorNode3);
    addActorToMovie(movie, actorNode4);
    addActorToMovie(movie, actorNode5);
}

void insertMovieTestCode() {
    // WOUW ZO MOOIE CODE AMMAAI
    MovieData* movie1 = newMovie("Inception", 2010);
    MovieData* movie2 = newMovie("The Shawshank Redemption", 1994);
    MovieData* movie3 = newMovie("Pulp Fiction", 1994);
    MovieData* movie4 = newMovie("The Godfather", 1972);
    MovieData* movie5 = newMovie("Forrest Gump", 1994);

    MovieNode* movieNode1 = newMovieNode(movie1);
    MovieNode* movieNode2 = newMovieNode(movie2);
    MovieNode* movieNode3 = newMovieNode(movie3);
    MovieNode* movieNode4 = newMovieNode(movie4);
    MovieNode* movieNode5 = newMovieNode(movie5);

    MovieNode** head =&movieNode1;
    insertMovie(head, movieNode2);
    insertMovie(head, movieNode3);
    insertMovie(head, movieNode4);
    insertMovie(head, movieNode5);

    //FREE MEM
    free(movieNode1);
    free(movieNode2);
    free(movieNode3);
    free(movieNode4);
    free(movieNode5);
    free(movie1);
    free(movie2);
    free(movie3);
    free(movie4);
    free(movie5);
}

void deleteMovieTestCode(){
    MovieData* movie1 = newMovie("Inception", 2010);
    MovieData* movie2 = newMovie("The Shawshank Redemption", 1994);
    MovieData* movie3 = newMovie("Pulp Fiction", 1994);
    MovieData* movie4 = newMovie("The Godfather", 1972);
    MovieData* movie5 = newMovie("Forrest Gump", 1994);

    MovieNode* movieNode1 = newMovieNode(movie1);
    MovieNode* movieNode2 = newMovieNode(movie2);
    MovieNode* movieNode3 = newMovieNode(movie3);
    MovieNode* movieNode4 = newMovieNode(movie4);
    MovieNode* movieNode5 = newMovieNode(movie5);

    MovieNode** head =&movieNode1;
    insertMovie(head, movieNode2);
    insertMovie(head, movieNode3);
    insertMovie(head, movieNode4);
    insertMovie(head, movieNode5);

    deleteMovie(head, movie3);
}*/