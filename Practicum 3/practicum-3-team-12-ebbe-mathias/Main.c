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
    struct ActorNode* actors;
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

void movieTestCode();
void acteurTestCode();
void compareMoviesTestCode();
void insertMovieTestCode();

int main() {
    insertMovieTestCode();
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

// Functie om een nieuwe filmstructuur te maken
MovieNode* newMovieNode(MovieData* movie) {
    // Geheugen toewijzen
    MovieNode* new_node = (MovieNode*)malloc(sizeof(MovieNode));
    if (new_node == NULL) {
        printf("Geheugen kon niet worden toegewezen voor de nieuwe node.\n");
        exit(EXIT_FAILURE);
    }

    new_node->movie = movie;
    new_node->next = NULL;

    return new_node;
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
        // Head van linkedlist TODO: THIS IS SOMEHOW BAD FIX MATHIAS
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

void insertMovieTestCode() {
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
}
