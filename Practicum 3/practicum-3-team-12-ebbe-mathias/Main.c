#include <stdio.h>
#include <stdlib.h>

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
void movieTestCode();
ActorData* newActor(const char* name);
void acteurTestCode();

int main() {
    movieTestCode();
    acteurTestCode();
    return 0;
}

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