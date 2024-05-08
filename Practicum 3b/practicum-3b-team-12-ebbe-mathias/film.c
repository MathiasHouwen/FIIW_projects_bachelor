#include <stdio.h>
#include "film.h"

// Functie om een nieuwe movie struct te maken
MovieData newMovie(const char* name, int year) {
    MovieData movieData;
    movieData.name = name;
    movieData.year = year;
    movieData.actors = NULL; // leeg bij init, kan achteraf gevuld worden
    return movieData;
}

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