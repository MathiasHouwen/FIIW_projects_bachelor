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

MovieData* newMovie(const char* name, int year);
ActorData* newActor(const char* name);
int compareMovies(MovieData* movie1, MovieData* movie2);
void insertMovie(MovieNode** head, MovieNode* newNode);
MovieNode* newMovieNode(MovieData* movie);
int compareActors(ActorData* actor1, ActorData* actor2);
void insertActor(MovieNode* head, ActorNode* newNode);
ActorNode* newActorNode(ActorData* actor);
void deleteMovie(MovieNode** head, MovieData* movie);

void movieTestCode();
void acteurTestCode();
void compareMoviesTestCode();
void insertMovieTestCode();
void insertActorTestCode();
void deleteMovieTestCode();

int main() {
    deleteMovieTestCode();
    return 0;
}

/* =============================[Functies]===========================================*/

// Functie om een nieuwe filmstructuur te maken
MovieData* newMovie(const char* name, int year) {
    // Geheugen toewijzen
    MovieData* new_movie = (MovieData*)malloc(sizeof(MovieData));
    if (new_movie == NULL) {
        printf("Geheugen kon niet worden toegewezen voor de nieuwe film.\n");
        exit(EXIT_FAILURE);
    }

    new_movie->name = name;
    new_movie->year = year;

    // De lijst van acteurs initialiseren als leeg voor begin
    new_movie->actors = NULL;

    return new_movie;
}

// Functie om een nieuwe acteurstructuur te maken
ActorData* newActor(const char* name) {
    // Geheugen toewijzen
    ActorData* new_actor = (ActorData*)malloc(sizeof(ActorData));
    if (new_actor == NULL) {
        printf("Geheugen kon niet worden toegewezen voor de nieuwe acteur.\n");
        exit(EXIT_FAILURE);
    }

    new_actor->name = name;

    return new_actor;
}

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

MovieNode* newMovieNode(MovieData* movie) {
    MovieNode* new_node = (MovieNode*)malloc(sizeof(MovieNode));
    if (new_node == NULL) {
        printf("Geheugen kon niet worden toegewezen voor de nieuwe node.\n");
        exit(EXIT_FAILURE);
    }

    new_node->movie = movie;
    new_node->next = NULL;

    return new_node;
}

ActorNode* newActorNode(ActorData* actor){
    ActorNode* new_node = (ActorNode*)malloc(sizeof(ActorNode));
    if (new_node == NULL) {
        printf("Geheugen kon niet worden toegewezen voor de nieuwe node.\n");
        exit(EXIT_FAILURE);
    }

    new_node->actor = actor;
    new_node->next = NULL;
    new_node->previous = NULL;

    return new_node;
}
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
void insertActor(MovieNode* head, ActorNode* newNode){
    // Als er nog geen acteurs bij de films zijn
    MovieData *mover = head->movie;
    if(mover->actors == NULL){
        mover->actors = newNode;
        return;
    }

    ActorNode *current = mover->actors;
    ActorNode *prev = NULL;

    while (current != NULL && compareActors(newNode->actor, current->actor) > 0){
        // TRAVEL THRUE LIST
        prev = current;
        current = current->next;
    }

    if(prev == NULL) {
        // HEAD
        mover->actors = newNode;
        current->previous = newNode;
        newNode->next = current;
    } else if (current == NULL) {
        // TAIL
        prev->next = newNode;
        newNode->previous = prev;
    } else {
        prev->next = newNode;
        newNode->next = current;
        newNode->previous  = prev;
        current->previous = newNode;
    }
}

void insertMovie(MovieNode** head, MovieNode* newNode) {
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    // Ga door de lijst tot bij de plaats waar die moet geinsert worden
    while (current != NULL && compareMovies(newNode->movie, current->movie) > 0) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // Head van linkedlist
        newNode->next = *head;
        *head = newNode;
    } else if (current == NULL) {
        // Tail van de linkedlist
        prev->next = newNode;
        newNode->next = NULL;
    } else {
        // Middel van de linkedlist
        prev->next = newNode;
        newNode->next = current;
    }
}

void deleteMovie(MovieNode** head, MovieData* movie){
    MovieNode* current = *head;
    MovieNode* prev = NULL;

    while (current != NULL && compareMovies(movie, current->movie) > 0) {
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

    free(movie);
    free(current->movie);
    free(current);
}

/* =============================[TEST CODE]===========================================*/
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
    qsort(movies, sizeof(movies) / sizeof(movies[0]), sizeof(struct MovieData),
          (_CoreCrtNonSecureSearchSortCompareFunction) compareMovies);

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

    insertActor(movie, actorNode1);
    insertActor(movie, actorNode2);
    insertActor(movie, actorNode3);
    insertActor(movie, actorNode4);
    insertActor(movie, actorNode5);
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
}